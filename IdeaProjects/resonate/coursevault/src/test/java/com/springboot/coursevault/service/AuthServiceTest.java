package com.springboot.coursevault.service;

import com.springboot.coursevault.auth.AuthService;
import com.springboot.coursevault.auth.SignupRequest;
import com.springboot.coursevault.user.UserRepository;
import com.springboot.coursevault.auth.CaptchaService;
import com.springboot.coursevault.auth.VerificationCodeRepository;
import com.springboot.coursevault.user.User;
import com.springboot.coursevault.user.UserDTO;
import com.springboot.coursevault.auth.LoginRequest;
import com.springboot.coursevault.auth.VerificationCode;


import org.springframework.web.server.ResponseStatusException;
import com.springboot.coursevault.util.JwtUtil;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.client.RestTemplate;

import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.*;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
class AuthServiceTest {

    @Mock
    private UserRepository userRepository;

    @Mock
    private VerificationCodeRepository codeRepository;

    @Mock
    private RestTemplate restTemplate;

    @Mock
    private CaptchaService captchaService;

    @Mock
    private JwtUtil jwtUtil;

    @Mock
    private PasswordEncoder passwordEncoder;

    @InjectMocks
    private AuthService authService;

    private User testUser;
    private final String rawPassword = "password123";

    @BeforeEach
    void setUp() {
        testUser = new User();
        testUser.setId(1L);
        testUser.setFullName("Test User");
        testUser.setEmail("test@example.com");
        testUser.setPassword("encoded-password");
        testUser.setRole("STUDENT");
        testUser.setSecurityQuestion("What is your pet's name?");
        testUser.setSecurityAnswer("$2a$hashed");
    }

    @Test
    void testLogin_Success() {
        LoginRequest request = new LoginRequest();
        request.setEmail("test@example.com");
        request.setPassword(rawPassword);
        request.setCaptchaToken("valid-captcha-token");

        when(captchaService.verify(eq("valid-captcha-token"), eq("127.0.0.1"))).thenReturn(true);
        when(userRepository.findByEmail(anyString())).thenReturn(Optional.of(testUser));
        when(passwordEncoder.matches(rawPassword, testUser.getPassword())).thenReturn(true);
        when(jwtUtil.generateToken(anyString(), anyString(), anyLong())).thenReturn("mocked-jwt-token");

        UserDTO result = authService.login(request, "127.0.0.1");

        assertNotNull(result);
        assertEquals("test@example.com", result.getEmail());
        assertEquals("STUDENT", result.getRole());
    }

    @Test
    void testLogin_PendingTeacherBlocked() {
        testUser.setRole("PENDING_TEACHER");
        LoginRequest request = new LoginRequest();
        request.setEmail("test@example.com");
        request.setPassword(rawPassword);
        request.setCaptchaToken("valid-captcha-token");

        when(captchaService.verify(eq("valid-captcha-token"), eq("127.0.0.1"))).thenReturn(true);
        when(userRepository.findByEmail(anyString())).thenReturn(Optional.of(testUser));

        ResponseStatusException ex = assertThrows(ResponseStatusException.class,
                () -> authService.login(request, "127.0.0.1"));
        assertTrue(ex.getReason() != null && ex.getReason().contains("pending"));
    }

    @Test
    void testInitiateSignup_Success() {
        SignupRequest request = new SignupRequest();
        request.setEmail("newuser@example.com");
        request.setFullName("New User");

        when(userRepository.findByEmail(anyString())).thenReturn(Optional.empty());

        assertDoesNotThrow(() -> authService.initiateSignup(request));

        verify(codeRepository).deleteByEmailAndType("newuser@example.com", "SIGNUP");
        verify(codeRepository).save(any(VerificationCode.class));
        verify(restTemplate).postForObject(eq("http://notification-service/api/notifications/send-code"), any(), eq(String.class));
    }
}

