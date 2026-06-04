package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.LoginRequest;
import com.springboot.coursevault.dto.SignupRequest;
import com.springboot.coursevault.dto.UserDTO;
import com.springboot.coursevault.dto.VerifyCodeRequest;
import com.springboot.coursevault.service.AuthService;
import jakarta.servlet.http.HttpServletRequest;
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
    public ResponseEntity<String> initiateSignup(@Valid @RequestBody SignupRequest request) {
        authService.initiateSignup(request);
        return ResponseEntity.ok("Verification code sent to " + request.getEmail());
    }

    @PostMapping("/signup/verify")
    public ResponseEntity<UserDTO> verifySignup(@Valid @RequestBody VerifyCodeRequest verifyRequest) {
        UserDTO result = authService.verifySignup(
                verifyRequest.getEmail(),
                verifyRequest.getCode(),
                verifyRequest.getSignupData()
        );
        return ResponseEntity.status(HttpStatus.CREATED).body(result);
    }

    @PostMapping("/login")
    public ResponseEntity<UserDTO> login(@Valid @RequestBody LoginRequest request, HttpServletRequest httpRequest) {
        UserDTO result = authService.login(request, httpRequest.getRemoteAddr());
        return ResponseEntity.ok(result);
    }

    @PostMapping("/password-reset/initiate")
    public ResponseEntity<String> initiateReset(
            @RequestParam String email,
            @RequestParam String question,
            @RequestParam String answer) {
        String msg = authService.initiatePasswordReset(email, question, answer);
        return ResponseEntity.ok(msg);
    }

    @PostMapping("/password-reset/finalize")
    public ResponseEntity<String> finalizeReset(
            @RequestParam String email,
            @RequestParam String code,
            @RequestParam String newPassword) {
        authService.finalizePasswordReset(email, code, newPassword);
        return ResponseEntity.ok("Password updated successfully");
    }
}