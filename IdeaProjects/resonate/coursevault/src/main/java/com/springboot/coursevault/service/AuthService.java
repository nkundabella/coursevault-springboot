package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.LoginRequest;
import com.springboot.coursevault.dto.SignupRequest;
import com.springboot.coursevault.dto.UserDTO;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.UserRepository;
import org.mindrot.jbcrypt.BCrypt;
import org.springframework.stereotype.Service;

@Service
public class AuthService {

    private final UserRepository userRepository;

    public AuthService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public UserDTO login(LoginRequest request) {
        User user = userRepository.findByEmail(request.getEmail())
                .orElseThrow(() -> new RuntimeException("User not found"));

        if (!BCrypt.checkpw(request.getPassword(), user.getPassword())) {
            throw new RuntimeException("Invalid password");
        }

        return new UserDTO(user);
    }

    public UserDTO signup(SignupRequest request) {
        if (userRepository.findByEmail(request.getEmail()).isPresent()) {
            throw new RuntimeException("Email already exists");
        }

        User user = new User();
        user.setFullName(request.getFullName());
        user.setEmail(request.getEmail());
        user.setPassword(BCrypt.hashpw(request.getPassword(), BCrypt.gensalt()));
        
        // Logic for role assignment (Admin for the first user)
        if (userRepository.count() == 0) {
            user.setRole("ADMIN");
        } else {
            // Default to STUDENT, unless TEACHER is requested
            String assignedRole = "STUDENT";
            if ("TEACHER".equalsIgnoreCase(request.getRole())) {
                assignedRole = "PENDING_TEACHER"; // Teachers need approval usually
            }
            user.setRole(assignedRole);
        }

        user.setSecurityQuestion(request.getSecurityQuestion());
        user.setSecurityAnswer(request.getSecurityAnswer());

        User savedUser = userRepository.save(user);
        return new UserDTO(savedUser);
    }
}
