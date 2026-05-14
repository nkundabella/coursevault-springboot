package com.springboot.coursevault.service;

import com.springboot.coursevault.model.SystemConfig;
import com.springboot.coursevault.repository.SystemConfigRepository;
import org.springframework.mail.SimpleMailMessage;
import org.springframework.mail.javamail.JavaMailSenderImpl;
import org.springframework.stereotype.Service;

import java.util.Properties;

@Service
public class MailService {

    private final SystemConfigRepository configRepository;
    private JavaMailSenderImpl mailSender;

    public MailService(SystemConfigRepository configRepository) {
        this.configRepository = configRepository;
        initializeMailSender();
    }

    public void initializeMailSender() {
        SystemConfig config = configRepository.findAll().stream().findFirst().orElse(null);
        if (config != null && config.getSmtpHost() != null) {
            mailSender = new JavaMailSenderImpl();
            mailSender.setHost(config.getSmtpHost());
            mailSender.setPort(Integer.parseInt(config.getSmtpPort()));
            mailSender.setUsername(config.getSmtpUser());
            mailSender.setPassword(config.getSmtpPass());

            Properties props = mailSender.getJavaMailProperties();
            props.put("mail.transport.protocol", "smtp");
            props.put("mail.smtp.auth", "true");
            props.put("mail.smtp.starttls.enable", "true");
            props.put("mail.debug", "true");
        }
    }

    public void sendVerificationCode(String to, String code) {
        if (mailSender == null) {
            initializeMailSender();
        }
        
        if (mailSender == null) {
            System.err.println("Mail sender not configured. Code was: " + code);
            return;
        }

        SimpleMailMessage message = new SimpleMailMessage();
        message.setFrom(mailSender.getUsername());
        message.setTo(to);
        message.setSubject("CourseVault | Your Verification Code");
        message.setText("Your CourseVault verification code is:\n\n" + code + "\n\nThis code expires in 10 minutes.");

        mailSender.send(message);
    }
}
