package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.*;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.service.CurrentUserService;
import com.springboot.coursevault.service.UserService;
import jakarta.validation.Valid;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/users")
public class UserController {

    private final UserService userService;
    private final CurrentUserService currentUserService;

    public UserController(UserService userService, CurrentUserService currentUserService) {
        this.userService = userService;
        this.currentUserService = currentUserService;
    }

    @GetMapping("/me")
    public ResponseEntity<UserDTO> getMe() {
        User user = currentUserService.requireCurrentUser();
        return ResponseEntity.ok(userService.getProfile(user));
    }

    @PutMapping("/me/profile")
    public ResponseEntity<UserDTO> updateProfile(@Valid @RequestBody UpdateProfileRequest request) {
        User user = currentUserService.requireCurrentUser();
        return ResponseEntity.ok(userService.updateProfile(user, request));
    }

    @PutMapping("/me/password")
    public ResponseEntity<String> changePassword(@Valid @RequestBody ChangePasswordRequest request) {
        User user = currentUserService.requireCurrentUser();
        userService.changePassword(user, request);
        return ResponseEntity.ok("Password updated successfully");
    }

    @PutMapping("/me/security")
    public ResponseEntity<UserDTO> updateSecurity(@Valid @RequestBody UpdateSecurityRequest request) {
        User user = currentUserService.requireCurrentUser();
        return ResponseEntity.ok(userService.updateSecurity(user, request));
    }
}