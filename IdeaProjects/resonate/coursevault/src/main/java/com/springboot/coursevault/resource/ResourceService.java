package com.springboot.coursevault.resource;

import com.springboot.coursevault.user.User;
import com.springboot.coursevault.bookmark.Bookmark;
import com.springboot.coursevault.subject.CreateSubjectRequest;

import com.springboot.coursevault.subject.CreateSubjectRequest;
import com.springboot.coursevault.resource.ResourceDTO;
import com.springboot.coursevault.util.InputSanitizer;
import com.springboot.coursevault.exception.GlobalExceptionHandler;
import com.springboot.coursevault.bookmark.Bookmark;
import com.springboot.coursevault.user.User;
import com.springboot.coursevault.bookmark.BookmarkRepository;
import com.springboot.coursevault.resource.ResourceRepository;
import com.springboot.coursevault.security.AuthorizationService;
import org.springframework.core.io.FileSystemResource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.data.domain.PageRequest;
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
    public com.springboot.coursevault.resource.Resource getResourceEntity(Long id) {
        return resourceRepository.findById(id)
                .orElseThrow(() -> GlobalExceptionHandler.notFound("Resource not found"));
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
        com.springboot.coursevault.resource.Resource resource = getResourceEntity(id);
        authorizationService.assertCanDeleteResource(actor, resource);

        fileStorageService.deleteIfExists(resource.getFilePath());
        bookmarkRepository.deleteByResource(resource);
        resourceRepository.delete(resource);
    }

    @Transactional
    public void toggleBookmark(User user, Long resourceId) {
        com.springboot.coursevault.resource.Resource resource = getResourceEntity(resourceId);

        bookmarkRepository.findByUserIdAndResource(user.getId(), resource)
                .ifPresentOrElse(
                        bookmarkRepository::delete,
                        () -> bookmarkRepository.save(new Bookmark(user.getId(), resource))
                );
    }

    @Transactional(readOnly = true)
    public List<ResourceDTO> getRecentResources(int limit) {
        int size = Math.min(Math.max(limit, 1), 50);
        return resourceRepository.findByOrderByIdDesc(PageRequest.of(0, size)).stream()
                .map(resourceDtoMapper::toDto)
                .collect(Collectors.toList());
    }

    @Transactional(readOnly = true)
    public List<ResourceDTO> getMaterialsForUser(User user) {
        String role = user.getRole();
        if ("ADMIN".equals(role)) {
            return getAllResources();
        }
        if ("TEACHER".equals(role)) {
            return resourceRepository.findByUploaderId(user.getId()).stream()
                    .map(resourceDtoMapper::toDto)
                    .collect(Collectors.toList());
        }
        return getBookmarksByUser(user);
    }

    @Transactional
    public ResourceDTO updateResource(Long id, CreateSubjectRequest request, User actor) {
        com.springboot.coursevault.resource.Resource resource = getResourceEntity(id);
        authorizationService.assertCanEditResource(actor, resource);

        if (request.getResourceTitle() != null && !request.getResourceTitle().isBlank()) {
            resource.setTitle(InputSanitizer.cleanText(request.getResourceTitle(), 200));
        }
        resource.setYear(InputSanitizer.parseIntInRange(String.valueOf(request.getYear()), 1, 3, resource.getYear()));
        resource.setTerm(InputSanitizer.parseIntInRange(String.valueOf(request.getTerm()), 1, 3, resource.getTerm()));
        if (request.getType() != null) {
            authorizationService.validateResourceTypeForRole(actor, request.getType());
            resource.setType(InputSanitizer.cleanResourceType(request.getType()));
        }
        return resourceDtoMapper.toDto(resourceRepository.save(resource));
    }

    @Transactional(readOnly = true)
    public List<ResourceDTO> getBookmarksByUser(User user) {
        return bookmarkRepository.findByUserId(user.getId()).stream()
                .map(bookmark -> resourceDtoMapper.toDto(bookmark.getResource()))
                .collect(Collectors.toList());
    }

    @Transactional(readOnly = true)
    public ResponseEntity<org.springframework.core.io.Resource> buildDownloadResponse(Long id, String mode) {
        com.springboot.coursevault.resource.Resource entity = getResourceEntity(id);
        Path filePath = fileStorageService.resolveStoredFile(entity.getFilePath());

        if (!Files.exists(filePath) || !Files.isRegularFile(filePath)) {
            throw GlobalExceptionHandler.notFound("File not found on disk");
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
