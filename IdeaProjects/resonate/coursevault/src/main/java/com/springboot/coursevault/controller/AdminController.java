package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.UserDTO;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.UserRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/api/admin")
public class AdminController {

    private final UserRepository userRepository;

    public AdminController(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @GetMapping("/pending-teachers")
    public ResponseEntity<List<UserDTO>> getPendingTeachers() {
        List<UserDTO> pending = userRepository.findByRole("PENDING_TEACHER").stream()
                .map(UserDTO::new)
                .collect(Collectors.toList());
        return ResponseEntity.ok(pending);
    }

    @PostMapping("/approve-teacher/{userId}")
    public ResponseEntity<?> approveTeacher(@PathVariable Long userId) {
        User user = userRepository.findById(userId).orElse(null);
        if (user != null && "PENDING_TEACHER".equals(user.getRole())) {
            user.setRole("TEACHER");
            userRepository.save(user);
            return ResponseEntity.ok("Teacher approved");
        }
        return ResponseEntity.badRequest().body("User not found or not a pending teacher");
    }
}