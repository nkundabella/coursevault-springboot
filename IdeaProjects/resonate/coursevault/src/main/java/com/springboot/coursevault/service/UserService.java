package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.*;
import com.springboot.coursevault.exception.GlobalExceptionHandler;
import com.springboot.coursevault.model.SystemConfig;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.SystemConfigRepository;
import com.springboot.coursevault.repository.UserRepository;
import com.springboot.coursevault.util.InputSanitizer;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
public class UserService {

    private final UserRepository userRepository;
    private final SystemConfigRepository configRepository;
    private final PasswordEncoder passwordEncoder;
    private final AuthService authService;

    public UserService(UserRepository userRepository,
                       SystemConfigRepository configRepository,
                       PasswordEncoder passwordEncoder,
                       AuthService authService) {
        this.userRepository = userRepository;
        this.configRepository = configRepository;
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

    @Transactional(readOnly = true)
    public SystemConfigDTO getConfig() {
        SystemConfig config = configRepository.findAll().stream().findFirst().orElse(new SystemConfig());
        SystemConfigDTO dto = new SystemConfigDTO();
        dto.setId(config.getId());
        dto.setSmtpHost(config.getSmtpHost());
        dto.setSmtpPort(config.getSmtpPort());
        dto.setSmtpUser(config.getSmtpUser());
        dto.setSmtpPasswordConfigured(config.getSmtpPass() != null && !config.getSmtpPass().isBlank());
        return dto;
    }
}