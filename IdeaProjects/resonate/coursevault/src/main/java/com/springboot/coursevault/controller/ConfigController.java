package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.SystemConfigDTO;
import com.springboot.coursevault.model.SystemConfig;
import com.springboot.coursevault.repository.SystemConfigRepository;
import com.springboot.coursevault.service.MailService;
import com.springboot.coursevault.service.UserService;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/config")
@PreAuthorize("hasRole('ADMIN')")
public class ConfigController {

    private final SystemConfigRepository configRepository;
    private final MailService mailService;
    private final UserService userService;

    public ConfigController(SystemConfigRepository configRepository,
                            MailService mailService,
                            UserService userService) {
        this.configRepository = configRepository;
        this.mailService = mailService;
        this.userService = userService;
    }

    @GetMapping
    public ResponseEntity<SystemConfigDTO> getConfig() {
        return ResponseEntity.ok(userService.getConfig());
    }

    @PostMapping("/smtp")
    public ResponseEntity<?> updateSmtp(@RequestBody SystemConfig config) {
        SystemConfig existing = configRepository.findAll().stream().findFirst().orElse(new SystemConfig());
        existing.setSmtpHost(config.getSmtpHost() != null ? config.getSmtpHost().trim() : null);
        existing.setSmtpPort(config.getSmtpPort() != null ? config.getSmtpPort().trim() : null);
        existing.setSmtpUser(config.getSmtpUser() != null ? config.getSmtpUser().trim() : null);
        if (config.getSmtpPass() != null && !config.getSmtpPass().isBlank()) {
            existing.setSmtpPass(config.getSmtpPass());
        }
        
        configRepository.save(existing);
        mailService.initializeMailSender();
        
        return ResponseEntity.ok("SMTP configuration updated successfully");
    }
}