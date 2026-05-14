package com.springboot.coursevault.repository;

import com.springboot.coursevault.model.Resource;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface ResourceRepository extends JpaRepository<Resource, Long> {
    Optional<Resource> findByFileHash(String fileHash);
    List<Resource> findBySubjectId(Long subjectId);
    List<Resource> findByUploaderId(Long uploaderId);
    List<Resource> findByTitleContainingIgnoreCase(String title);
}
