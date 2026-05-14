package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.LoginRequest;
import com.springboot.coursevault.dto.SignupRequest;
import com.springboot.coursevault.dto.UserDTO;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.UserRepository;
import org.mindrot.jbcrypt.BCrypt;
import org.springframework.stereotype.Service;

@Service
public class AuthService {

    private final UserRepository userRepository;
    private final VerificationCodeRepository codeRepository;
    private final MailService mailService;

    public AuthService(UserRepository userRepository, VerificationCodeRepository codeRepository, MailService mailService) {
        this.userRepository = userRepository;
        this.codeRepository = codeRepository;
        this.mailService = mailService;
    }

    public UserDTO login(LoginRequest request) {
        User user = userRepository.findByEmail(request.getEmail())
                .orElseThrow(() -> new RuntimeException("User not found"));

        if (!BCrypt.checkpw(request.getPassword(), user.getPassword())) {
            throw new RuntimeException("Invalid password");
        }

        return new UserDTO(user);
    }

    @Transactional
    public void initiateSignup(SignupRequest request) {
        if (userRepository.findByEmail(request.getEmail()).isPresent()) {
            throw new RuntimeException("Email already exists");
        }

        String code = String.format("%06d", new java.util.Random().nextInt(1000000));
        codeRepository.deleteByEmailAndType(request.getEmail(), "SIGNUP");
        codeRepository.save(new VerificationCode(request.getEmail(), code, "SIGNUP", 10));
        
        mailService.sendVerificationCode(request.getEmail(), code);
    }

    @Transactional
    public UserDTO verifySignup(String email, String code, SignupRequest originalRequest) {
        VerificationCode vc = codeRepository.findByEmailAndCodeAndType(email, code, "SIGNUP")
                .orElseThrow(() -> new RuntimeException("Invalid or expired code"));

        if (vc.isExpired()) {
            throw new RuntimeException("Code has expired");
        }

        User user = new User();
        user.setFullName(originalRequest.getFullName());
        user.setEmail(email);
        user.setPassword(BCrypt.hashpw(originalRequest.getPassword(), BCrypt.gensalt()));
        
        if (userRepository.count() == 0) {
            user.setRole("ADMIN");
        } else {
            String assignedRole = "STUDENT";
            if ("TEACHER".equalsIgnoreCase(originalRequest.getRole())) {
                assignedRole = "PENDING_TEACHER";
            }
            user.setRole(assignedRole);
        }

        user.setSecurityQuestion(originalRequest.getSecurityQuestion());
        user.setSecurityAnswer(originalRequest.getSecurityAnswer());

        User savedUser = userRepository.save(user);
        codeRepository.delete(vc);
        return new UserDTO(savedUser);
    }

    @Transactional
    public String initiatePasswordReset(String email, String question, String answer) {
        User user = userRepository.findByEmail(email)
                .orElseThrow(() -> new RuntimeException("User not found"));

        if (!user.getSecurityQuestion().equals(question) || 
            !user.getSecurityAnswer().equalsIgnoreCase(answer.trim())) {
            throw new RuntimeException("Security question or answer is incorrect");
        }

        String code = String.format("%06d", new java.util.Random().nextInt(1000000));
        codeRepository.deleteByEmailAndType(email, "RESET");
        codeRepository.save(new VerificationCode(email, code, "RESET", 10));
        
        mailService.sendVerificationCode(email, code);
        return "Verification code sent to email";
    }

    @Transactional
    public void finalizePasswordReset(String email, String code, String newPassword) {
        VerificationCode vc = codeRepository.findByEmailAndCodeAndType(email, code, "RESET")
                .orElseThrow(() -> new RuntimeException("Invalid or expired code"));

        if (vc.isExpired()) {
            throw new RuntimeException("Code has expired");
        }

        User user = userRepository.findByEmail(email)
                .orElseThrow(() -> new RuntimeException("User not found"));

        user.setPassword(BCrypt.hashpw(newPassword, BCrypt.gensalt()));
        userRepository.save(user);
        codeRepository.delete(vc);
    }
}
