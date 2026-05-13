package com.springboot.coursevault.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;

public class CreateSubjectRequest {
    @NotBlank(message = "Subject name is required")
    @Size(max = 120)
    private String name;

    private String iconClass;

    @Size(max = 500)
    private String description;

    @NotBlank(message = "Resource title is required")
    @Size(max = 200)
    private String resourceTitle;

    private int year;
    private int term;

    @NotBlank(message = "Resource type is required")
    private String type;

    public CreateSubjectRequest() {}

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public String getIconClass() { return iconClass; }
    public void setIconClass(String iconClass) { this.iconClass = iconClass; }

    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }

    public String getResourceTitle() { return resourceTitle; }
    public void setResourceTitle(String resourceTitle) { this.resourceTitle = resourceTitle; }

    public int getYear() { return year; }
    public void setYear(int year) { this.year = year; }

    public int getTerm() { return term; }
    public void setTerm(int term) { this.term = term; }

    public String getType() { return type; }
    public void setType(String type) { this.type = type; }
}
