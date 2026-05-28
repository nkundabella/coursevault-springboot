package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.ResourceDTO;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.service.CurrentUserService;
import com.springboot.coursevault.service.ResourceService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/api/materials")
public class MaterialsController {

    private final ResourceService resourceService;
    private final CurrentUserService currentUserService;

    public MaterialsController(ResourceService resourceService, CurrentUserService currentUserService) {
        this.resourceService = resourceService;
        this.currentUserService = currentUserService;
    }

    @GetMapping
    public ResponseEntity<List<ResourceDTO>> getMaterials() {
        User user = currentUserService.requireCurrentUser();
        return ResponseEntity.ok(resourceService.getMaterialsForUser(user));
    }
}