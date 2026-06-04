package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.LoginRequest;
import com.springboot.coursevault.dto.SignupRequest;
import com.springboot.coursevault.dto.UserDTO;
import com.springboot.coursevault.dto.SendCodeRequest;
import com.springboot.coursevault.exception.GlobalExceptionHandler;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.model.VerificationCode;
import com.springboot.coursevault.repository.UserRepository;
import com.springboot.coursevault.repository.VerificationCodeRepository;
import com.springboot.coursevault.util.InputSanitizer;
import com.springboot.coursevault.util.JwtUtil;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.client.RestTemplate;

@Service
public class AuthService {

    private final UserRepository userRepository;
    private final VerificationCodeRepository codeRepository;
    private final RestTemplate restTemplate;
    private final CaptchaService captchaService;
    private final JwtUtil jwtUtil;
    private final PasswordEncoder passwordEncoder;

    public AuthService(UserRepository userRepository,
                       VerificationCodeRepository codeRepository,
                       RestTemplate restTemplate,
                       CaptchaService captchaService,
                       JwtUtil jwtUtil,
                       PasswordEncoder passwordEncoder) {
        this.userRepository = userRepository;
        this.codeRepository = codeRepository;
        this.restTemplate = restTemplate;
        this.captchaService = captchaService;
        this.jwtUtil = jwtUtil;
        this.passwordEncoder = passwordEncoder;
    }

    public UserDTO login(LoginRequest request, String clientIp) {
        String captchaToken = request.getCaptchaToken();
        if (captchaToken == null || captchaToken.isBlank()) {
            throw GlobalExceptionHandler.badRequest("CAPTCHA verification is required.");
        }
        if (!captchaService.verify(captchaToken, clientIp)) {
            throw GlobalExceptionHandler.badRequest("CAPTCHA verification failed. Please try again.");
        }

        User user = userRepository.findByEmail(request.getEmail())
                .orElseThrow(() -> GlobalExceptionHandler.badRequest("No account found with that email."));

        if ("PENDING_TEACHER".equals(user.getRole())) {
            throw GlobalExceptionHandler.forbidden(
                    "Your teacher account is pending admin approval. You cannot log in yet.");
        }

        if (!passwordEncoder.matches(request.getPassword(), user.getPassword())) {
            throw GlobalExceptionHandler.badRequest("Incorrect password.");
        }

        UserDTO userDTO = new UserDTO(user);
        userDTO.setToken(jwtUtil.generateToken(user.getEmail(), user.getRole(), user.getId()));
        return userDTO;
    }

    @Transactional
    public void initiateSignup(SignupRequest request) {
        if (userRepository.findByEmail(request.getEmail()).isPresent()) {
            throw GlobalExceptionHandler.badRequest("Email already exists");
        }

        String code = String.format("%06d", new java.util.Random().nextInt(1_000_000));
        codeRepository.deleteByEmailAndType(request.getEmail(), "SIGNUP");
        codeRepository.save(new VerificationCode(request.getEmail(), code, "SIGNUP", 10));

        sendCode(request.getEmail(), code);
    }

    @Transactional
    public UserDTO verifySignup(String email, String code, SignupRequest originalRequest) {
        if (!email.equals(originalRequest.getEmail())) {
            throw GlobalExceptionHandler.badRequest(
                    "Email mismatch: The verification email must match the signup email.");
        }

        VerificationCode vc = codeRepository.findByEmailAndCodeAndType(email, code, "SIGNUP")
                .orElseThrow(() -> GlobalExceptionHandler.badRequest("Invalid verification code or code expired."));

        if (vc.isExpired()) {
            throw GlobalExceptionHandler.badRequest("Verification code has expired. Please request a new one.");
        }

        User user = new User();
        user.setFullName(InputSanitizer.cleanText(originalRequest.getFullName(), 100));
        user.setEmail(email);
        user.setPassword(passwordEncoder.encode(originalRequest.getPassword()));

        if (userRepository.count() == 0) {
            user.setRole("ADMIN");
        } else {
            String assignedRole = "STUDENT";
            if ("TEACHER".equalsIgnoreCase(originalRequest.getRole())) {
                assignedRole = "PENDING_TEACHER";
            }
            user.setRole(assignedRole);
        }

        user.setSecurityQuestion(InputSanitizer.cleanText(originalRequest.getSecurityQuestion(), 150));
        user.setSecurityAnswer(hashSecurityAnswer(originalRequest.getSecurityAnswer()));

        User savedUser = userRepository.save(user);
        codeRepository.delete(vc);

        UserDTO userDTO = new UserDTO(savedUser);
        userDTO.setToken(jwtUtil.generateToken(savedUser.getEmail(), savedUser.getRole(), savedUser.getId()));
        return userDTO;
    }

    @Transactional
    public String initiatePasswordReset(String email, String question, String answer) {
        User user = userRepository.findByEmail(email)
                .orElseThrow(() -> GlobalExceptionHandler.badRequest("User not found"));

        if (!matchesSecurityAnswer(user, answer)
                || user.getSecurityQuestion() == null
                || !user.getSecurityQuestion().equals(question)) {
            throw GlobalExceptionHandler.badRequest("Security question or answer is incorrect");
        }

        String code = String.format("%06d", new java.util.Random().nextInt(1_000_000));
        codeRepository.deleteByEmailAndType(email, "RESET");
        codeRepository.save(new VerificationCode(email, code, "RESET", 10));

        sendCode(email, code);
        return "Verification code sent to email";
    }

    @Transactional
    public void finalizePasswordReset(String email, String code, String newPassword) {
        VerificationCode vc = codeRepository.findByEmailAndCodeAndType(email, code, "RESET")
                .orElseThrow(() -> GlobalExceptionHandler.badRequest("Invalid or expired code"));

        if (vc.isExpired()) {
            throw GlobalExceptionHandler.badRequest("Code has expired");
        }

        User user = userRepository.findByEmail(email)
                .orElseThrow(() -> GlobalExceptionHandler.badRequest("User not found"));

        user.setPassword(passwordEncoder.encode(newPassword));
        userRepository.save(user);
        codeRepository.delete(vc);
    }

    private void sendCode(String email, String code) {
        try {
            SendCodeRequest req = new SendCodeRequest(email, code);
            restTemplate.postForObject("http://notification-service/api/notifications/send-code", req, String.class);
        } catch (Exception e) {
            System.err.println("Notification Service failed to send verification code: " + e.getMessage());
        }
    }

    public String hashSecurityAnswer(String answer) {
        if (answer == null || answer.isBlank()) {
            return passwordEncoder.encode("");
        }
        return passwordEncoder.encode(answer.trim().toLowerCase());
    }

    public boolean matchesSecurityAnswer(User user, String plainAnswer) {
        if (user.getSecurityAnswer() == null || plainAnswer == null) {
            return false;
        }
        String normalized = plainAnswer.trim().toLowerCase();
        String stored = user.getSecurityAnswer();
        if (stored.startsWith("$2a$") || stored.startsWith("$2b$") || stored.startsWith("$2y$")) {
            return passwordEncoder.matches(normalized, stored);
        }
        return stored.equalsIgnoreCase(plainAnswer.trim());
    }
}
