package com.springboot.coursevault.service;

import com.springboot.coursevault.resource.FileStorageService;

import org.springframework.web.server.ResponseStatusException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

class FileStorageServiceTest {

    @TempDir
    Path tempDir;

    private FileStorageService fileStorageService;

    @BeforeEach
    void setUp() {
        fileStorageService = new FileStorageService(tempDir.toString());
    }

    @Test
    void displayFileName_stripsTimestampPrefix() {
        assertEquals("lecture.pdf", FileStorageService.displayFileName("12345_lecture.pdf"));
    }

    @Test
    void resolveStoredFile_rejectsPathTraversal() {
        assertThrows(ResponseStatusException.class, () -> fileStorageService.resolveStoredFile("../secret.txt"));
    }

    @Test
    void resolveStoredFile_stripsLegacyUploadsPrefix() {
        Path resolved = fileStorageService.resolveStoredFile("uploads/file.pdf");
        assertTrue(resolved.endsWith("file.pdf"));
    }
}
