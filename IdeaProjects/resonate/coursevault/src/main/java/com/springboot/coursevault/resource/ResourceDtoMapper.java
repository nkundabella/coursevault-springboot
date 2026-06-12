package com.springboot.coursevault.resource;

import com.springboot.coursevault.user.User;

import com.springboot.coursevault.resource.ResourceDTO;
import com.springboot.coursevault.resource.Resource;
import com.springboot.coursevault.user.User;
import com.springboot.coursevault.user.UserRepository;
import org.springframework.stereotype.Component;

@Component
public class ResourceDtoMapper {

    private final UserRepository userRepository;

    public ResourceDtoMapper(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public ResourceDTO toDto(Resource resource) {
        Long uploaderId = resource.getUploaderId();
        String uploaderName = "Unknown";
        if (uploaderId != null) {
            uploaderName = userRepository.findById(uploaderId)
                    .map(User::getFullName)
                    .orElse("Unknown");
        }
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
