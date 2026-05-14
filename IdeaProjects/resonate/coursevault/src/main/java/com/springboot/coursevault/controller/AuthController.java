package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.LoginRequest;
import com.springboot.coursevault.dto.SignupRequest;
import com.springboot.coursevault.dto.UserDTO;
import com.springboot.coursevault.service.AuthService;
import jakarta.validation.Valid;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/auth")
public class AuthController {

    private final AuthService authService;

    public AuthController(AuthService authService) {
        this.authService = authService;
    }

    @PostMapping("/signup/initiate")
    public ResponseEntity<?> initiateSignup(@Valid @RequestBody SignupRequest request) {
        try {
            authService.initiateSignup(request);
            return ResponseEntity.ok("Verification code sent to " + request.getEmail());
        } catch (RuntimeException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }

    @PostMapping("/signup/verify")
    public ResponseEntity<?> verifySignup(@Valid @RequestBody VerifyCodeRequest verifyRequest, @RequestBody SignupRequest originalRequest) {
        try {
            UserDTO result = authService.verifySignup(verifyRequest.getEmail(), verifyRequest.getCode(), originalRequest);
            return ResponseEntity.status(HttpStatus.CREATED).body(result);
        } catch (RuntimeException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }

    @PostMapping("/login")
    public ResponseEntity<?> login(@Valid @RequestBody LoginRequest request) {
        try {
            UserDTO result = authService.login(request);
            return ResponseEntity.ok(result);
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body(e.getMessage());
        }
    }

    @PostMapping("/password-reset/initiate")
    public ResponseEntity<?> initiateReset(@RequestParam String email, @RequestParam String question, @RequestParam String answer) {
        try {
            String msg = authService.initiatePasswordReset(email, question, answer);
            return ResponseEntity.ok(msg);
        } catch (RuntimeException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }

    @PostMapping("/password-reset/finalize")
    public ResponseEntity<?> finalizeReset(@RequestParam String email, @RequestParam String code, @RequestParam String newPassword) {
        try {
            authService.finalizePasswordReset(email, code, newPassword);
            return ResponseEntity.ok("Password updated successfully");
        } catch (RuntimeException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }
}
