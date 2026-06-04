package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.CreateSubjectRequest;
import com.springboot.coursevault.dto.ResourceDTO;
import com.springboot.coursevault.dto.SubjectDTO;
import com.springboot.coursevault.exception.GlobalExceptionHandler;
import com.springboot.coursevault.model.Resource;
import com.springboot.coursevault.model.Subject;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.BookmarkRepository;
import com.springboot.coursevault.repository.ResourceRepository;
import com.springboot.coursevault.repository.SubjectRepository;
import com.springboot.coursevault.security.AuthorizationService;
import com.springboot.coursevault.util.InputSanitizer;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class SubjectService {

    private final SubjectRepository subjectRepository;
    private final ResourceRepository resourceRepository;
    private final BookmarkRepository bookmarkRepository;
    private final FileStorageService fileStorageService;
    private final ResourceDtoMapper resourceDtoMapper;
    private final AuthorizationService authorizationService;

    public SubjectService(SubjectRepository subjectRepository,
                          ResourceRepository resourceRepository,
                          BookmarkRepository bookmarkRepository,
                          FileStorageService fileStorageService,
                          ResourceDtoMapper resourceDtoMapper,
                          AuthorizationService authorizationService) {
        this.subjectRepository = subjectRepository;
        this.resourceRepository = resourceRepository;
        this.bookmarkRepository = bookmarkRepository;
        this.fileStorageService = fileStorageService;
        this.resourceDtoMapper = resourceDtoMapper;
        this.authorizationService = authorizationService;
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
                .orElseThrow(() -> GlobalExceptionHandler.notFound("Subject not found"));
        return convertToDTO(subject);
    }

    @Transactional
    public SubjectDTO addSubject(CreateSubjectRequest request, MultipartFile file, User uploader) throws IOException {
        authorizationService.assertCanCreateSubject(uploader);
        authorizationService.validateResourceTypeForRole(uploader, request.getType());

        String fileHash = fileStorageService.calculateHash(file);
        if (resourceRepository.findByFileHash(fileHash).isPresent()) {
            throw GlobalExceptionHandler.badRequest("This resource already exists (duplicate detected by hash)");
        }

        String savedFileName = fileStorageService.store(file);

        Subject subject = subjectRepository.findByNameIgnoreCase(request.getName())
                .orElseGet(() -> {
                    Subject s = new Subject();
                    s.setName(InputSanitizer.cleanText(request.getName(), 120));
                    s.setIconClass(InputSanitizer.cleanIconClass(request.getIconClass()));
                    s.setDescription(InputSanitizer.cleanText(request.getDescription(), 500));
                    return subjectRepository.save(s);
                });

        Resource resource = new Resource();
        resource.setTitle(InputSanitizer.cleanText(request.getResourceTitle(), 200));
        resource.setFilePath(savedFileName);
        resource.setYear(InputSanitizer.parseIntInRange(String.valueOf(request.getYear()), 1, 3, 1));
        resource.setTerm(InputSanitizer.parseIntInRange(String.valueOf(request.getTerm()), 1, 3, 1));
        resource.setType(InputSanitizer.cleanResourceType(request.getType()));
        resource.setSubject(subject);
        resource.setUploaderId(uploader.getId());
        resource.setFileHash(fileHash);

        resourceRepository.save(resource);
        return convertToDTO(subjectRepository.findById(subject.getId()).orElse(subject));
    }

    @Transactional
    public SubjectDTO createSubjectMetadata(CreateSubjectRequest request, User actor) {
        authorizationService.assertCanCreateSubject(actor);

        Subject subject = new Subject();
        subject.setName(InputSanitizer.cleanText(request.getName(), 120));
        subject.setIconClass(InputSanitizer.cleanIconClass(request.getIconClass()));
        subject.setDescription(InputSanitizer.cleanText(request.getDescription(), 500));
        return convertToDTO(subjectRepository.save(subject));
    }

    @Transactional
    public SubjectDTO updateSubject(Long id, CreateSubjectRequest request, User actor) {
        authorizationService.assertCanCreateSubject(actor);

        Subject subject = subjectRepository.findById(id)
                .orElseThrow(() -> GlobalExceptionHandler.notFound("Subject not found"));

        if (request.getName() != null && !request.getName().isBlank()) {
            subject.setName(InputSanitizer.cleanText(request.getName(), 120));
        }
        if (request.getIconClass() != null) {
            subject.setIconClass(InputSanitizer.cleanIconClass(request.getIconClass()));
        }
        if (request.getDescription() != null) {
            subject.setDescription(InputSanitizer.cleanText(request.getDescription(), 500));
        }
        return convertToDTO(subjectRepository.save(subject));
    }

    @Transactional
    public ResourceDTO addResourceToSubject(Long subjectId, CreateSubjectRequest request,
                                            MultipartFile file, User uploader) throws IOException {
        authorizationService.assertCanUpload(uploader);
        authorizationService.validateResourceTypeForRole(uploader, request.getType());

        Subject subject = subjectRepository.findById(subjectId)
                .orElseThrow(() -> GlobalExceptionHandler.notFound("Subject not found"));

        String fileHash = fileStorageService.calculateHash(file);
        if (resourceRepository.findByFileHash(fileHash).isPresent()) {
            throw GlobalExceptionHandler.badRequest(
                    "This resource already exists (duplicate detected by hash)");
        }

        String savedFileName = fileStorageService.store(file);

        com.springboot.coursevault.model.Resource resource = new com.springboot.coursevault.model.Resource();
        resource.setTitle(InputSanitizer.cleanText(request.getResourceTitle(), 200));
        resource.setFilePath(savedFileName);
        resource.setYear(InputSanitizer.parseIntInRange(String.valueOf(request.getYear()), 1, 3, 1));
        resource.setTerm(InputSanitizer.parseIntInRange(String.valueOf(request.getTerm()), 1, 3, 1));
        resource.setType(InputSanitizer.cleanResourceType(request.getType()));
        resource.setSubject(subject);
        resource.setUploaderId(uploader.getId());
        resource.setFileHash(fileHash);

        return resourceDtoMapper.toDto(resourceRepository.save(resource));
    }

    @Transactional
    public void deleteSubject(Long id, User actor) {
        authorizationService.assertCanDeleteSubject(actor);

        Subject subject = subjectRepository.findById(id)
                .orElseThrow(() -> GlobalExceptionHandler.notFound("Subject not found"));

        for (Resource res : subject.getResources()) {
            fileStorageService.deleteIfExists(res.getFilePath());
            bookmarkRepository.deleteByResource(res);
        }
        subjectRepository.delete(subject);
    }

    private SubjectDTO convertToDTO(Subject subject) {
        List<ResourceDTO> resourceDTOs = subject.getResources().stream()
                .map(resourceDtoMapper::toDto)
                .collect(Collectors.toList());
        return new SubjectDTO(
                subject.getId(),
                subject.getName(),
                subject.getIconClass(),
                subject.getDescription(),
                resourceDTOs
        );
    }
}
