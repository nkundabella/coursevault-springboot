package com.springboot.coursevault.portal;

import com.springboot.coursevault.portal.SystemConfigDTO;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

@RestController
@RequestMapping("/api/config")
@PreAuthorize("hasRole('ADMIN')")
public class ConfigController {

    private final RestTemplate restTemplate;
    private static final String NOTIFICATION_SERVICE_URL = "http://notification-service/api/config";

    public ConfigController(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    @GetMapping
    public ResponseEntity<SystemConfigDTO> getConfig() {
        try {
            SystemConfigDTO dto = restTemplate.getForObject(NOTIFICATION_SERVICE_URL, SystemConfigDTO.class);
            return ResponseEntity.ok(dto);
        } catch (Exception e) {
            return ResponseEntity.internalServerError().build();
        }
    }

    @PostMapping("/smtp")
    public ResponseEntity<?> updateSmtp(@RequestBody Object config) {
        try {
            Object response = restTemplate.postForObject(NOTIFICATION_SERVICE_URL + "/smtp", config, Object.class);
            return ResponseEntity.ok(response);
        } catch (Exception e) {
            return ResponseEntity.internalServerError().body("Failed to update SMTP configuration: " + e.getMessage());
        }
    }
}