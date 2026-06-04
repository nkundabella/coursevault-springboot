package com.springboot.coursevault.security;

import org.springframework.web.server.ResponseStatusException;
import com.springboot.coursevault.model.Resource;
import com.springboot.coursevault.model.User;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertThrows;

class AuthorizationServiceTest {

    private AuthorizationService authorizationService;
    private User admin;
    private User teacher;
    private User student;
    private User pending;
    private Resource resource;

    @BeforeEach
    void setUp() {
        authorizationService = new AuthorizationService();

        admin = user(1L, "ADMIN");
        teacher = user(2L, "TEACHER");
        student = user(3L, "STUDENT");
        pending = user(4L, "PENDING_TEACHER");

        resource = new Resource();
        resource.setId(10L);
        User uploader = user(99L, "STUDENT");
        resource.setUploaderId(uploader.getId());
    }

    private User user(Long id, String role) {
        User u = new User();
        u.setId(id);
        u.setRole(role);
        return u;
    }

    @Test
    void pendingTeacherCannotUpload() {
        assertThrows(ResponseStatusException.class, () -> authorizationService.assertCanUpload(pending));
    }

    @Test
    void studentCannotUploadNotes() {
        assertThrows(ResponseStatusException.class,
                () -> authorizationService.validateResourceTypeForRole(student, "NOTES"));
    }

    @Test
    void studentCanUploadGroupPresentation() {
        assertDoesNotThrow(
                () -> authorizationService.validateResourceTypeForRole(student, "GROUP_PRESENTATION"));
    }

    @Test
    void teacherCannotUploadGroupPresentation() {
        assertThrows(ResponseStatusException.class,
                () -> authorizationService.validateResourceTypeForRole(teacher, "GROUP_PRESENTATION"));
    }

    @Test
    void adminCanDeleteAnyResource() {
        assertDoesNotThrow(() -> authorizationService.assertCanDeleteResource(admin, resource));
    }

    @Test
    void uploaderCanDeleteOwnResource() {
        resource.setUploaderId(student.getId());
        assertDoesNotThrow(() -> authorizationService.assertCanDeleteResource(student, resource));
    }
}
