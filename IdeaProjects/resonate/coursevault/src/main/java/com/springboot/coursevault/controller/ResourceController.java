package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.ResourceDTO;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.service.CurrentUserService;
import com.springboot.coursevault.service.ResourceService;
import org.springframework.core.io.Resource;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/resources")
public class ResourceController {

    private final ResourceService resourceService;
    private final CurrentUserService currentUserService;

    public ResourceController(ResourceService resourceService, CurrentUserService currentUserService) {
        this.resourceService = resourceService;
        this.currentUserService = currentUserService;
    }

    @GetMapping
    public ResponseEntity<List<ResourceDTO>> getAllResources() {
        return ResponseEntity.ok(resourceService.getAllResources());
    }

    @GetMapping("/subject/{subjectId}")
    public ResponseEntity<List<ResourceDTO>> getResourcesBySubject(@PathVariable Long subjectId) {
        return ResponseEntity.ok(resourceService.getResourcesBySubject(subjectId));
    }

    @GetMapping("/{id}/download")
    public ResponseEntity<Resource> download(
            @PathVariable Long id,
            @RequestParam(defaultValue = "attachment") String mode) {
        return resourceService.buildDownloadResponse(id, mode);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteResource(@PathVariable Long id) {
        User user = currentUserService.requireCurrentUser();
        resourceService.deleteResource(id, user);
        return ResponseEntity.noContent().build();
    }

    @PostMapping("/{id}/bookmark")
    public ResponseEntity<String> toggleBookmark(@PathVariable Long id) {
        User user = currentUserService.requireCurrentUser();
        resourceService.toggleBookmark(user, id);
        return ResponseEntity.ok("Bookmark status toggled");
    }

    @GetMapping("/bookmarks")
    public ResponseEntity<List<ResourceDTO>> getMyBookmarks() {
        User user = currentUserService.requireCurrentUser();
        return ResponseEntity.ok(resourceService.getBookmarksByUser(user));
    }
}
