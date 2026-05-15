package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.ResourceDTO;
import com.springboot.coursevault.model.Bookmark;
import com.springboot.coursevault.model.Resource;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.BookmarkRepository;
import com.springboot.coursevault.repository.ResourceRepository;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class ResourceService {

    private final ResourceRepository resourceRepository;
    private final BookmarkRepository bookmarkRepository;

    @Value("${file.upload-dir}")
    private String uploadDir;

    public ResourceService(ResourceRepository resourceRepository, BookmarkRepository bookmarkRepository) {
        this.resourceRepository = resourceRepository;
        this.bookmarkRepository = bookmarkRepository;
    }

    public List<ResourceDTO> getAllResources() {
        return resourceRepository.findAll().stream()
                .map(this::convertToDTO)
                .collect(Collectors.toList());
    }

    public List<ResourceDTO> getResourcesBySubject(Long subjectId) {
        return resourceRepository.findBySubjectId(subjectId).stream()
                .map(this::convertToDTO)
                .collect(Collectors.toList());
    }

    @Transactional
    public void deleteResource(Long id) {
        Resource resource = resourceRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Resource not found"));

        // Delete from filesystem
        try {
            Files.deleteIfExists(Paths.get(uploadDir).resolve(resource.getFilePath()));
        } catch (IOException e) {
            // Log error
        }

        resourceRepository.delete(resource);
    }

    @Transactional
    public void toggleBookmark(User user, Long resourceId) {
        Resource resource = resourceRepository.findById(resourceId)
                .orElseThrow(() -> new RuntimeException("Resource not found"));

        bookmarkRepository.findByUserAndResource(user, resource)
                .ifPresentOrElse(
                        bookmarkRepository::delete,
                        () -> bookmarkRepository.save(new Bookmark(user, resource))
                );
    }

    public List<ResourceDTO> getBookmarksByUser(User user) {
        return bookmarkRepository.findByUser(user).stream()
                .map(bookmark -> convertToDTO(bookmark.getResource()))
                .collect(Collectors.toList());
    }

    private ResourceDTO convertToDTO(Resource resource) {
        Long uploaderId = (resource.getUploader() != null) ? resource.getUploader().getId() : null;
        String uploaderName = (resource.getUploader() != null) ? resource.getUploader().getFullName() : "Unknown";
        return new ResourceDTO(
                resource.getId(),
                resource.getTitle(),
                resource.getFilePath(),
                resource.getYear(),
                resource.getTerm(),
                resource.getType(),
                uploaderId,
                uploaderName
        );
    }
}