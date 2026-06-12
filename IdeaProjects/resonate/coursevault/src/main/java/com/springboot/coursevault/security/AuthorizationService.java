package com.springboot.coursevault.security;

import com.springboot.coursevault.user.User;
import com.springboot.coursevault.resource.Resource;


import com.springboot.coursevault.exception.GlobalExceptionHandler;
import org.springframework.stereotype.Service;

@Service
public class AuthorizationService {

    public void assertCanUpload(User user) {
        if (user == null) {
            throw GlobalExceptionHandler.forbidden("Authentication required");
        }
        String role = user.getRole();
        if ("PENDING_TEACHER".equals(role)) {
            throw GlobalExceptionHandler.forbidden("Your teacher account is pending approval. You cannot upload yet.");
        }
        if (!"ADMIN".equals(role) && !"TEACHER".equals(role) && !"STUDENT".equals(role)) {
            throw GlobalExceptionHandler.forbidden("You are not allowed to upload resources");
        }
    }

    public void assertCanCreateSubject(User user) {
        if (user == null) {
            throw GlobalExceptionHandler.forbidden("Authentication required");
        }
        String role = user.getRole();
        if (!"ADMIN".equals(role) && !"TEACHER".equals(role)) {
            throw GlobalExceptionHandler.forbidden("Only teachers and admins can create subjects");
        }
    }

    public void validateResourceTypeForRole(User user, String type) {
        assertCanUpload(user);
        String cleaned = type != null ? type.toUpperCase() : "NOTES";
        String role = user.getRole();

        if ("STUDENT".equals(role)) {
            if (!"GROUP_PRESENTATION".equals(cleaned) && !"OTHER".equals(cleaned)) {
                throw GlobalExceptionHandler.forbidden(
                        "Students can only upload Group Presentations or Other resources");
            }
        } else if ("TEACHER".equals(role) || "ADMIN".equals(role)) {
            if ("GROUP_PRESENTATION".equals(cleaned)) {
                throw GlobalExceptionHandler.forbidden(
                        "Teachers cannot upload Group Presentations. These are for students.");
            }
        }
    }

    public void assertCanDeleteSubject(User user) {
        if (user == null) {
            throw GlobalExceptionHandler.forbidden("Authentication required");
        }
        String role = user.getRole();
        if (!"ADMIN".equals(role) && !"TEACHER".equals(role)) {
            throw GlobalExceptionHandler.forbidden("Only teachers and admins can delete subjects");
        }
    }

    public void assertCanDeleteResource(User user, Resource resource) {
        if (user == null) {
            throw GlobalExceptionHandler.forbidden("Authentication required");
        }
        String role = user.getRole();
        if ("ADMIN".equals(role) || "TEACHER".equals(role)) {
            return;
        }
        if (resource.getUploaderId() != null
                && resource.getUploaderId().equals(user.getId())) {
            return;
        }
        throw GlobalExceptionHandler.forbidden("You are not allowed to delete this resource");
    }

    public void assertCanEditResource(User user, Resource resource) {
        if (user == null) {
            throw GlobalExceptionHandler.forbidden("Authentication required");
        }
        if ("ADMIN".equals(user.getRole())) {
            return;
        }
        if (resource.getUploaderId() != null
                && resource.getUploaderId().equals(user.getId())) {
            return;
        }
        throw GlobalExceptionHandler.forbidden("You are not allowed to edit this resource");
    }

    public void assertAdminOrTeacher(User user) {
        if (user == null) {
            throw GlobalExceptionHandler.forbidden("Authentication required");
        }
        String role = user.getRole();
        if (!"ADMIN".equals(role) && !"TEACHER".equals(role)) {
            throw GlobalExceptionHandler.forbidden("Only teachers and admins can perform this action");
        }
    }
}
