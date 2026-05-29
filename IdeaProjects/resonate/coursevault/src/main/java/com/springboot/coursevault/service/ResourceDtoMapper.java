package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.ResourceDTO;
import com.springboot.coursevault.model.Resource;
import org.springframework.stereotype.Component;

@Component
public class ResourceDtoMapper {

    public ResourceDTO toDto(Resource resource) {
        Long uploaderId = resource.getUploader() != null ? resource.getUploader().getId() : null;
        String uploaderName = resource.getUploader() != null
                ? resource.getUploader().getFullName()
                : "Unknown";
        String fileName = FileStorageService.displayFileName(resource.getFilePath());
        String downloadUrl = "/api/resources/" + resource.getId() + "/download";

        Long subjectId = resource.getSubject() != null ? resource.getSubject().getId() : null;
        String subjectName = resource.getSubject() != null ? resource.getSubject().getName() : null;

        return new ResourceDTO(
                resource.getId(),
                resource.getTitle(),
                fileName,
                downloadUrl,
                resource.getYear(),
                resource.getTerm(),
                resource.getType(),
                uploaderId,
                uploaderName,
                subjectId,
                subjectName
        );
    }
}
