package com.springboot.coursevault.dto;

import java.util.List;

public class SubjectDTO {
    private Long id;
    private String name;
    private String iconClass;
    private String description;
    private List<ResourceDTO> resources;

    public SubjectDTO() {}

    public SubjectDTO(Long id, String name, String iconClass, String description, List<ResourceDTO> resources) {
        this.id = id;
        this.name = name;
        this.iconClass = iconClass;
        this.description = description;
        this.resources = resources;
    }

    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public String getIconClass() { return iconClass; }
    public void setIconClass(String iconClass) { this.iconClass = iconClass; }

    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }

    public List<ResourceDTO> getResources() { return resources; }
    public void setResources(List<ResourceDTO> resources) { this.resources = resources; }
}
