package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.AdminStatsDTO;
import com.springboot.coursevault.dto.UserDTO;
import com.springboot.coursevault.service.UserService;
import com.springboot.coursevault.exception.GlobalExceptionHandler;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.UserRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/api/admin")
@PreAuthorize("hasRole('ADMIN')")
public class AdminController {

    private final UserRepository userRepository;
    private final UserService userService;

    public AdminController(UserRepository userRepository, UserService userService) {
        this.userRepository = userRepository;
        this.userService = userService;
    }

    @GetMapping("/stats")
    public ResponseEntity<AdminStatsDTO> getStats() {
        return ResponseEntity.ok(userService.getAdminStats());
    }

    @GetMapping("/pending-teachers")
    public ResponseEntity<List<UserDTO>> getPendingTeachers() {
        List<UserDTO> pending = userRepository.findByRole("PENDING_TEACHER").stream()
                .map(UserDTO::new)
                .collect(Collectors.toList());
        return ResponseEntity.ok(pending);
    }

    @PostMapping("/approve-teacher/{userId}")
    public ResponseEntity<String> approveTeacher(@PathVariable Long userId) {
        User user = userRepository.findById(userId)
                .orElseThrow(() -> GlobalExceptionHandler.badRequest("User not found"));
        if (!"PENDING_TEACHER".equals(user.getRole())) {
            throw GlobalExceptionHandler.badRequest("User is not a pending teacher");
        }
        user.setRole("TEACHER");
        userRepository.save(user);
        return ResponseEntity.ok("Teacher approved");
    }

    @PostMapping("/decline-teacher/{userId}")
    public ResponseEntity<String> declineTeacher(@PathVariable Long userId) {
        User user = userRepository.findById(userId)
                .orElseThrow(() -> GlobalExceptionHandler.badRequest("User not found"));
        if (!"PENDING_TEACHER".equals(user.getRole())) {
            throw GlobalExceptionHandler.badRequest("User is not a pending teacher");
        }
        user.setRole("STUDENT");
        userRepository.save(user);
        return ResponseEntity.ok("Teacher application declined; user is now a student");
    }
}