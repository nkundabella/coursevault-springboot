package com.springboot.coursevault.resource;

import com.springboot.coursevault.user.User;

import com.springboot.coursevault.user.User;

import com.springboot.coursevault.resource.ResourceDTO;
import com.springboot.coursevault.user.User;
import com.springboot.coursevault.user.CurrentUserService;
import com.springboot.coursevault.resource.ResourceService;
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