package com.springboot.coursevault.resource;

import com.springboot.coursevault.exception.GlobalExceptionHandler;
import com.springboot.coursevault.util.FileValidator;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

@Service
public class FileStorageService {

    private final Path uploadRoot;

    public FileStorageService(@Value("${file.upload-dir}") String uploadDir) {
        this.uploadRoot = Paths.get(uploadDir).toAbsolutePath().normalize();
    }

    public String store(MultipartFile file) throws IOException {
        if (file == null || file.isEmpty()) {
            throw GlobalExceptionHandler.badRequest("File is required");
        }

        String originalFileName = file.getOriginalFilename();
        if (originalFileName == null || originalFileName.isBlank()) {
            throw GlobalExceptionHandler.badRequest("Invalid file name");
        }

        String lowerCase = originalFileName.toLowerCase();
        int dotIndex = lowerCase.lastIndexOf('.');
        if (dotIndex < 0) {
            throw GlobalExceptionHandler.badRequest("File must have an extension");
        }
        String extension = lowerCase.substring(dotIndex + 1);

        try (InputStream is = file.getInputStream()) {
            if (!FileValidator.isSafeAndValid(is, extension)) {
                throw GlobalExceptionHandler.badRequest("Invalid file signature or type");
            }
        }

        String savedFileName = System.currentTimeMillis() + "_"
                + originalFileName.replaceAll("[^a-zA-Z0-9._-]", "_");

        Files.createDirectories(uploadRoot);
        Files.copy(file.getInputStream(), uploadRoot.resolve(savedFileName));
        return savedFileName;
    }

    public String calculateHash(MultipartFile file) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hashBytes = digest.digest(file.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException | IOException e) {
            throw GlobalExceptionHandler.badRequest("Error calculating file hash");
        }
    }

    public Path resolveStoredFile(String storedPath) {
        if (storedPath == null || storedPath.isBlank()) {
            throw GlobalExceptionHandler.badRequest("Invalid file path");
        }

        String normalized = storedPath.replace("\\", "/");
        while (normalized.startsWith("/")) {
            normalized = normalized.substring(1);
        }
        if (normalized.contains("..") || normalized.matches("^[a-zA-Z]:.*")) {
            throw GlobalExceptionHandler.badRequest("Invalid file path");
        }
        if (normalized.startsWith("uploads/")) {
            normalized = normalized.substring("uploads/".length());
        }

        Path resolved = uploadRoot.resolve(normalized).normalize();
        if (!resolved.startsWith(uploadRoot)) {
            throw GlobalExceptionHandler.badRequest("Invalid file path");
        }
        return resolved;
    }

    public void deleteIfExists(String storedPath) {
        try {
            Path path = resolveStoredFile(storedPath);
            Files.deleteIfExists(path);
        } catch (RuntimeException ignored) {
            // Invalid path — nothing to delete on disk
        } catch (IOException ignored) {
            // Best effort delete
        }
    }

    public static String displayFileName(String storedPath) {
        if (storedPath == null) {
            return "download";
        }
        String name = Paths.get(storedPath.replace("\\", "/")).getFileName().toString();
        int underscore = name.indexOf('_');
        if (underscore >= 0 && underscore < name.length() - 1) {
            return name.substring(underscore + 1);
        }
        return name;
    }

    public static String detectMimeType(String displayName, Path filePath) {
        String mimeType = null;
        try {
            mimeType = Files.probeContentType(filePath);
        } catch (IOException ignored) {
        }
        if (mimeType != null) {
            return mimeType;
        }

        String lower = displayName.toLowerCase();
        if (lower.endsWith(".pdf")) return "application/pdf";
        if (lower.endsWith(".jpg") || lower.endsWith(".jpeg")) return "image/jpeg";
        if (lower.endsWith(".png")) return "image/png";
        if (lower.endsWith(".txt")) return "text/plain";
        if (lower.endsWith(".doc")) return "application/msword";
        if (lower.endsWith(".docx")) {
            return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
        }
        if (lower.endsWith(".ppt")) return "application/vnd.ms-powerpoint";
        if (lower.endsWith(".pptx")) {
            return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
        }
        return "application/octet-stream";
    }
}
