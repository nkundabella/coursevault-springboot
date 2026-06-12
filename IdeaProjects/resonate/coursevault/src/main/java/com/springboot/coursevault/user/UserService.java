package com.springboot.coursevault.user;

import com.springboot.coursevault.auth.AuthService;
import com.springboot.coursevault.portal.AdminStatsDTO;
import com.springboot.coursevault.auth.ChangePasswordRequest;

import com.springboot.coursevault.exception.GlobalExceptionHandler;
import com.springboot.coursevault.user.User;
import com.springboot.coursevault.user.UserRepository;
import com.springboot.coursevault.util.InputSanitizer;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
public class UserService {

    private final UserRepository userRepository;
    private final PasswordEncoder passwordEncoder;
    private final AuthService authService;

    public UserService(UserRepository userRepository,
                       PasswordEncoder passwordEncoder,
                       AuthService authService) {
        this.userRepository = userRepository;
        this.passwordEncoder = passwordEncoder;
        this.authService = authService;
    }

    @Transactional(readOnly = true)
    public UserDTO getProfile(User user) {
        return new UserDTO(user);
    }

    @Transactional
    public UserDTO updateProfile(User user, UpdateProfileRequest request) {
        user.setFullName(InputSanitizer.cleanText(request.getFullName(), 100));
        return new UserDTO(userRepository.save(user));
    }

    @Transactional
    public void changePassword(User user, ChangePasswordRequest request) {
        if (!passwordEncoder.matches(request.getCurrentPassword(), user.getPassword())) {
            throw GlobalExceptionHandler.badRequest("Current password is incorrect");
        }
        if (!request.getNewPassword().equals(request.getConfirmPassword())) {
            throw GlobalExceptionHandler.badRequest("New passwords do not match");
        }
        user.setPassword(passwordEncoder.encode(request.getNewPassword()));
        userRepository.save(user);
    }

    @Transactional
    public UserDTO updateSecurity(User user, UpdateSecurityRequest request) {
        if (request.getSecurityQuestion() != null && !request.getSecurityQuestion().isBlank()) {
            user.setSecurityQuestion(InputSanitizer.cleanText(request.getSecurityQuestion(), 150));
        }
        if (request.getSecurityAnswer() != null && !request.getSecurityAnswer().isBlank()) {
            user.setSecurityAnswer(authService.hashSecurityAnswer(request.getSecurityAnswer()));
        }
        return new UserDTO(userRepository.save(user));
    }

    @Transactional(readOnly = true)
    public AdminStatsDTO getAdminStats() {
        AdminStatsDTO stats = new AdminStatsDTO();
        stats.setTotalUsers(userRepository.count());
        stats.setAdminCount(userRepository.findByRole("ADMIN").size());
        stats.setTeacherCount(userRepository.findByRole("TEACHER").size());
        stats.setStudentCount(userRepository.findByRole("STUDENT").size());
        stats.setPendingTeacherCount(userRepository.findByRole("PENDING_TEACHER").size());
        return stats;
    }
}