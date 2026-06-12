package com.springboot.coursevault.resource;

import com.springboot.coursevault.bookmark.Bookmark;
import com.springboot.coursevault.user.User;
import com.springboot.coursevault.subject.CreateSubjectRequest;

import com.springboot.coursevault.user.User;
import com.springboot.coursevault.bookmark.Bookmark;
import com.springboot.coursevault.subject.CreateSubjectRequest;

import com.springboot.coursevault.subject.CreateSubjectRequest;
import com.springboot.coursevault.resource.ResourceDTO;
import com.springboot.coursevault.user.User;
import jakarta.validation.Valid;
import com.springboot.coursevault.user.CurrentUserService;
import com.springboot.coursevault.resource.ResourceService;
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

    @GetMapping("/recent")
    public ResponseEntity<List<ResourceDTO>> getRecentResources(
            @RequestParam(defaultValue = "10") int limit) {
        return ResponseEntity.ok(resourceService.getRecentResources(limit));
    }

    @PutMapping("/{id}")
    public ResponseEntity<ResourceDTO> updateResource(
            @PathVariable Long id,
            @Valid @RequestBody CreateSubjectRequest request) {
        User user = currentUserService.requireCurrentUser();
        return ResponseEntity.ok(resourceService.updateResource(id, request, user));
    }

    @GetMapping("/{id}/download")
    public ResponseEntity<org.springframework.core.io.Resource> download(
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
