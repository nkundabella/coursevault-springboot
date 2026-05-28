package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.ResourceDTO;
import com.springboot.coursevault.exception.ResourceNotFoundException;
import com.springboot.coursevault.model.Bookmark;
import com.springboot.coursevault.model.Resource;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.BookmarkRepository;
import com.springboot.coursevault.repository.ResourceRepository;
import com.springboot.coursevault.security.AuthorizationService;
import org.springframework.core.io.FileSystemResource;
import org.springframework.core.io.Resource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class ResourceService {

    private final ResourceRepository resourceRepository;
    private final BookmarkRepository bookmarkRepository;
    private final FileStorageService fileStorageService;
    private final ResourceDtoMapper resourceDtoMapper;
    private final AuthorizationService authorizationService;

    public ResourceService(ResourceRepository resourceRepository,
                           BookmarkRepository bookmarkRepository,
                           FileStorageService fileStorageService,
                           ResourceDtoMapper resourceDtoMapper,
                           AuthorizationService authorizationService) {
        this.resourceRepository = resourceRepository;
        this.bookmarkRepository = bookmarkRepository;
        this.fileStorageService = fileStorageService;
        this.resourceDtoMapper = resourceDtoMapper;
        this.authorizationService = authorizationService;
    }

    @Transactional(readOnly = true)
    public com.springboot.coursevault.model.Resource getResourceEntity(Long id) {
        return resourceRepository.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("Resource not found"));
    }

    @Transactional(readOnly = true)
    public List<ResourceDTO> getAllResources() {
        return resourceRepository.findAll().stream()
                .map(resourceDtoMapper::toDto)
                .collect(Collectors.toList());
    }

    @Transactional(readOnly = true)
    public List<ResourceDTO> getResourcesBySubject(Long subjectId) {
        return resourceRepository.findBySubjectId(subjectId).stream()
                .map(resourceDtoMapper::toDto)
                .collect(Collectors.toList());
    }

    @Transactional
    public void deleteResource(Long id, User actor) {
        com.springboot.coursevault.model.Resource resource = getResourceEntity(id);
        authorizationService.assertCanDeleteResource(actor, resource);

        fileStorageService.deleteIfExists(resource.getFilePath());
        bookmarkRepository.deleteByResource(resource);
        resourceRepository.delete(resource);
    }

    @Transactional
    public void toggleBookmark(User user, Long resourceId) {
        com.springboot.coursevault.model.Resource resource = getResourceEntity(resourceId);

        bookmarkRepository.findByUserAndResource(user, resource)
                .ifPresentOrElse(
                        bookmarkRepository::delete,
                        () -> bookmarkRepository.save(new Bookmark(user, resource))
                );
    }

    @Transactional(readOnly = true)
    public List<ResourceDTO> getBookmarksByUser(User user) {
        return bookmarkRepository.findByUser(user).stream()
                .map(bookmark -> resourceDtoMapper.toDto(bookmark.getResource()))
                .collect(Collectors.toList());
    }

    @Transactional(readOnly = true)
    public ResponseEntity<Resource> buildDownloadResponse(Long id, String mode) {
        com.springboot.coursevault.model.Resource entity = getResourceEntity(id);
        Path filePath = fileStorageService.resolveStoredFile(entity.getFilePath());

        if (!Files.exists(filePath) || !Files.isRegularFile(filePath)) {
            throw new ResourceNotFoundException("File not found on disk");
        }

        String displayName = FileStorageService.displayFileName(entity.getFilePath());
        String mimeType = FileStorageService.detectMimeType(displayName, filePath);
        FileSystemResource fileResource = new FileSystemResource(filePath);

        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.parseMediaType(mimeType));
        headers.set("X-Content-Type-Options", "nosniff");
        headers.set("Cache-Control", "private, max-age=3600");
        headers.set("X-Frame-Options", "SAMEORIGIN");
        headers.set("Referrer-Policy", "no-referrer");

        if ("view".equalsIgnoreCase(mode)) {
            headers.set(HttpHeaders.CONTENT_DISPOSITION, "inline; filename=\"" + displayName + "\"");
        } else {
            headers.set(HttpHeaders.CONTENT_DISPOSITION,
                    "attachment; filename=\"" + displayName + "\"");
        }

        return ResponseEntity.ok()
                .headers(headers)
                .contentLength(filePath.toFile().length())
                .body(fileResource);
    }
}
