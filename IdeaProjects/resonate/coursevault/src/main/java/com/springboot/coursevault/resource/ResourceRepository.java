package com.springboot.coursevault.resource;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import org.springframework.data.domain.Pageable;

import java.util.List;
import java.util.Optional;

@Repository
public interface ResourceRepository extends JpaRepository<Resource, Long> {
    Optional<Resource> findByFileHash(String fileHash);
    List<Resource> findBySubjectId(Long subjectId);
    List<Resource> findByUploaderId(Long uploaderId);
    List<Resource> findByTitleContainingIgnoreCase(String title);
    List<Resource> findByOrderByIdDesc(Pageable pageable);
}