package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.ResourceDTO;
import com.springboot.coursevault.dto.SubjectDTO;
import com.springboot.coursevault.dto.CreateSubjectRequest;
import com.springboot.coursevault.model.Resource;
import com.springboot.coursevault.model.Subject;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.BookmarkRepository;
import com.springboot.coursevault.repository.ResourceRepository;
import com.springboot.coursevault.repository.SubjectRepository;
import com.springboot.coursevault.util.FileValidator;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class SubjectService {

    private final SubjectRepository subjectRepository;
    private final ResourceRepository resourceRepository;
    private final BookmarkRepository bookmarkRepository;

    @Value("${file.upload-dir}")
    private String uploadDir;

    public SubjectService(SubjectRepository subjectRepository, ResourceRepository resourceRepository, BookmarkRepository bookmarkRepository) {
        this.subjectRepository = subjectRepository;
        this.resourceRepository = resourceRepository;
        this.bookmarkRepository = bookmarkRepository;
    }

    @Transactional(readOnly = true)
    public List<SubjectDTO> getAllSubjects() {
        return subjectRepository.findAll().stream()
                .map(this::convertToDTO)
                .collect(Collectors.toList());
    }

    @Transactional(readOnly = true)
    public SubjectDTO getSubjectById(Long id) {
        Subject subject = subjectRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Subject not found"));
        return convertToDTO(subject);
    }

    @Transactional
    public SubjectDTO addSubject(CreateSubjectRequest request, MultipartFile file, User uploader) throws IOException {
        if (file.isEmpty()) {
            throw new RuntimeException("File is required");
        }

        String originalFileName = file.getOriginalFilename();
        if (originalFileName == null) throw new RuntimeException("Invalid file name");
        
        String lowerCase = originalFileName.toLowerCase();
        String extension = lowerCase.substring(lowerCase.lastIndexOf('.') + 1);

        try (InputStream is = file.getInputStream()) {
            if (!FileValidator.isSafeAndValid(is, extension)) {
                throw new RuntimeException("Invalid file signature or type");
            }
        }

        String fileHash = calculateHash(file);
        if (resourceRepository.findByFileHash(fileHash).isPresent()) {
            throw new RuntimeException("This resource already exists (duplicate detected by hash)");
        }

        // Save file
        String savedFileName = System.currentTimeMillis() + "_" + originalFileName.replaceAll("[^a-zA-Z0-9._-]", "_");
        Path uploadPath = Paths.get(uploadDir);
        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }
        Files.copy(file.getInputStream(), uploadPath.resolve(savedFileName));

        Subject subject = subjectRepository.findByNameIgnoreCase(request.getName())
                .orElseGet(() -> {
                    Subject s = new Subject();
                    s.setName(request.getName());
                    s.setIconClass(request.getIconClass());
                    s.setDescription(request.getDescription());
                    return subjectRepository.save(s);
                });

        Resource resource = new Resource();
        resource.setTitle(request.getResourceTitle());
        resource.setFilePath(savedFileName);
        resource.setYear(request.getYear());
        resource.setTerm(request.getTerm());
        resource.setType(request.getType());
        resource.setSubject(subject);
        resource.setUploader(uploader);
        resource.setFileHash(fileHash);

        resourceRepository.save(resource);
        
        // Refresh subject to include new resource if needed, though with LAZY/Transactional it should be fine
        return convertToDTO(subject);
    }

    @Transactional
    public void deleteSubject(Long id) {
        Subject subject = subjectRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Subject not found"));

        for (Resource res : subject.getResources()) {
            try {
                Files.deleteIfExists(Paths.get(uploadDir).resolve(res.getFilePath()));
            } catch (IOException e) {
                // Log error but continue
            }
            // Delete associated bookmarks first to prevent constraint violations
            bookmarkRepository.deleteByResource(res);
        }
        subjectRepository.delete(subject);
    }

    private SubjectDTO convertToDTO(Subject subject) {
        List<ResourceDTO> resourceDTOs = subject.getResources().stream()
                .map(this::convertResourceToDTO)
                .collect(Collectors.toList());
        return new SubjectDTO(subject.getId(), subject.getName(), subject.getIconClass(), subject.getDescription(), resourceDTOs);
    }

    private ResourceDTO convertResourceToDTO(Resource resource) {
        Long uploaderId = (resource.getUploader() != null) ? resource.getUploader().getId() : null;
        String uploaderName = (resource.getUploader() != null) ? resource.getUploader().getFullName() : "Unknown";
        return new ResourceDTO(resource.getId(), resource.getTitle(), resource.getFilePath(), 
                resource.getYear(), resource.getTerm(), resource.getType(), uploaderId, uploaderName);
    }

    private String calculateHash(MultipartFile file) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hashBytes = digest.digest(file.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException | IOException e) {
            throw new RuntimeException("Error calculating file hash", e);
        }
    }
}