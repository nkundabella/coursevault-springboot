package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.LoginRequest;
import com.springboot.coursevault.dto.SignupRequest;
import com.springboot.coursevault.dto.UserDTO;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.model.VerificationCode;
import com.springboot.coursevault.repository.UserRepository;
import com.springboot.coursevault.repository.VerificationCodeRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.mindrot.jbcrypt.BCrypt;

import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
public class AuthServiceTest {

    @Mock
    private UserRepository userRepository;

    @Mock
    private VerificationCodeRepository codeRepository;

    @Mock
    private MailService mailService;

    @Mock
    private CaptchaService captchaService;

    @Mock
    private com.springboot.coursevault.util.JwtUtil jwtUtil;

    @InjectMocks
    private AuthService authService;

    private User testUser;
    private String rawPassword = "password123";

    @BeforeEach
    void setUp() {
        testUser = new User();
        testUser.setId(1L);
        testUser.setFullName("Test User");
        testUser.setEmail("test@example.com");
        testUser.setPassword(BCrypt.hashpw(rawPassword, BCrypt.gensalt()));
        testUser.setRole("STUDENT");
        testUser.setSecurityQuestion("What is your pet's name?");
        testUser.setSecurityAnswer("Fluffy");
    }

    @Test
    void testLogin_Success() {
        LoginRequest request = new LoginRequest();
        request.setEmail("test@example.com");
        request.setPassword(rawPassword);
        // Assuming no captcha token provided for this test

        when(userRepository.findByEmail(anyString())).thenReturn(Optional.of(testUser));
        when(jwtUtil.generateToken(anyString(), anyString())).thenReturn("mocked-jwt-token");

        UserDTO result = authService.login(request, "127.0.0.1");

        assertNotNull(result);
        assertEquals("test@example.com", result.getEmail());
        assertEquals("STUDENT", result.getRole());
    }

    @Test
    void testLogin_InvalidPassword() {
        LoginRequest request = new LoginRequest();
        request.setEmail("test@example.com");
        request.setPassword("wrongpassword");

        when(userRepository.findByEmail(anyString())).thenReturn(Optional.of(testUser));

        Exception exception = assertThrows(RuntimeException.class, () -> {
            authService.login(request, "127.0.0.1");
        });

        assertEquals("Incorrect password.", exception.getMessage());
    }

    @Test
    void testInitiateSignup_Success() {
        SignupRequest request = new SignupRequest();
        request.setEmail("newuser@example.com");
        request.setFullName("New User");

        when(userRepository.findByEmail(anyString())).thenReturn(Optional.empty());

        assertDoesNotThrow(() -> {
            authService.initiateSignup(request);
        });

        verify(codeRepository, times(1)).deleteByEmailAndType("newuser@example.com", "SIGNUP");
        verify(codeRepository, times(1)).save(any(VerificationCode.class));
        verify(mailService, times(1)).sendVerificationCode(eq("newuser@example.com"), anyString());
    }

    @Test
    void testInitiateSignup_EmailExists() {
        SignupRequest request = new SignupRequest();
        request.setEmail("test@example.com");

        when(userRepository.findByEmail(anyString())).thenReturn(Optional.of(testUser));

        Exception exception = assertThrows(RuntimeException.class, () -> {
            authService.initiateSignup(request);
        });

        assertEquals("Email already exists", exception.getMessage());
    }

    @Test
    void testVerifySignup_Success() {
        String email = "verify@example.com";
        String code = "123456";

        SignupRequest request = new SignupRequest();
        request.setEmail(email);
        request.setFullName("Verify User");
        request.setPassword("pass123");
        request.setRole("STUDENT");

        VerificationCode vc = new VerificationCode(email, code, "SIGNUP", 10);

        when(codeRepository.findByEmailAndCodeAndType(email, code, "SIGNUP")).thenReturn(Optional.of(vc));
        when(userRepository.count()).thenReturn(1L); // So it creates a STUDENT, not ADMIN
        when(userRepository.save(any(User.class))).thenAnswer(i -> {
            User u = i.getArgument(0);
            u.setId(2L);
            return u;
        });
        when(jwtUtil.generateToken(anyString(), anyString())).thenReturn("mocked-jwt-token");

        UserDTO result = authService.verifySignup(email, code, request);

        assertNotNull(result);
        assertEquals(email, result.getEmail());
        assertEquals("STUDENT", result.getRole());
        verify(codeRepository, times(1)).delete(vc);
    }
}
