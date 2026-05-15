package com.springboot.coursevault.controller;

import com.springboot.coursevault.model.SystemConfig;
import com.springboot.coursevault.repository.SystemConfigRepository;
import com.springboot.coursevault.service.MailService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/config")
public class ConfigController {

    private final SystemConfigRepository configRepository;
    private final MailService mailService;

    public ConfigController(SystemConfigRepository configRepository, MailService mailService) {
        this.configRepository = configRepository;
        this.mailService = mailService;
    }

    @PostMapping("/smtp")
    public ResponseEntity<?> updateSmtp(@RequestBody SystemConfig config) {
        SystemConfig existing = configRepository.findAll().stream().findFirst().orElse(new SystemConfig());
        existing.setSmtpHost(config.getSmtpHost() != null ? config.getSmtpHost().trim() : null);
        existing.setSmtpPort(config.getSmtpPort() != null ? config.getSmtpPort().trim() : null);
        existing.setSmtpUser(config.getSmtpUser() != null ? config.getSmtpUser().trim() : null);
        existing.setSmtpPass(config.getSmtpPass());
        
        configRepository.save(existing);
        mailService.initializeMailSender();
        
        return ResponseEntity.ok("SMTP configuration updated successfully");
    }
}