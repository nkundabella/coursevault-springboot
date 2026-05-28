package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.CreateSubjectRequest;
import com.springboot.coursevault.dto.ResourceDTO;
import com.springboot.coursevault.dto.SubjectDTO;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.service.CurrentUserService;
import com.springboot.coursevault.service.SubjectService;
import jakarta.validation.Valid;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.List;

@RestController
@RequestMapping("/api/subjects")
public class SubjectController {

    private final SubjectService subjectService;
    private final CurrentUserService currentUserService;

    public SubjectController(SubjectService subjectService, CurrentUserService currentUserService) {
        this.subjectService = subjectService;
        this.currentUserService = currentUserService;
    }

    @GetMapping
    public ResponseEntity<List<SubjectDTO>> getAllSubjects() {
        return ResponseEntity.ok(subjectService.getAllSubjects());
    }

    @GetMapping("/{id}")
    public ResponseEntity<SubjectDTO> getSubject(@PathVariable Long id) {
        return ResponseEntity.ok(subjectService.getSubjectById(id));
    }

    @PostMapping(consumes = "application/json")
    public ResponseEntity<SubjectDTO> createSubject(
            @Valid @RequestBody CreateSubjectRequest request) {
        User uploader = currentUserService.requireCurrentUser();
        SubjectDTO result = subjectService.createSubjectMetadata(request, uploader);
        return ResponseEntity.status(HttpStatus.CREATED).body(result);
    }

    @PutMapping("/{id}")
    public ResponseEntity<SubjectDTO> updateSubject(
            @PathVariable Long id,
            @Valid @RequestBody CreateSubjectRequest request) {
        User user = currentUserService.requireCurrentUser();
        return ResponseEntity.ok(subjectService.updateSubject(id, request, user));
    }

    @PostMapping(value = "/{id}/resources", consumes = {"multipart/form-data"})
    public ResponseEntity<ResourceDTO> addResourceToSubject(
            @PathVariable Long id,
            @RequestPart("file") MultipartFile file,
            @Valid @RequestPart("metadata") CreateSubjectRequest request) throws IOException {
        User uploader = currentUserService.requireCurrentUser();
        ResourceDTO result = subjectService.addResourceToSubject(id, request, file, uploader);
        return ResponseEntity.status(HttpStatus.CREATED).body(result);
    }

    @PostMapping(consumes = {"multipart/form-data"})
    public ResponseEntity<SubjectDTO> addSubject(
            @RequestPart("file") MultipartFile file,
            @Valid @RequestPart("metadata") CreateSubjectRequest request) throws IOException {
        User uploader = currentUserService.requireCurrentUser();
        SubjectDTO result = subjectService.addSubject(request, file, uploader);
        return ResponseEntity.status(HttpStatus.CREATED).body(result);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteSubject(@PathVariable Long id) {
        User user = currentUserService.requireCurrentUser();
        subjectService.deleteSubject(id, user);
        return ResponseEntity.noContent().build();
    }
}
