package com.springboot.coursevault.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import java.time.LocalDate;

public class CreateCalendarEventRequest {
    @NotBlank
    private String title;
    @NotNull
    private LocalDate date;
    private Integer term;
    private String category;
    private boolean major;
    private String description;

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }
    public LocalDate getDate() { return date; }
    public void setDate(LocalDate date) { this.date = date; }
    public Integer getTerm() { return term; }
    public void setTerm(Integer term) { this.term = term; }
    public String getCategory() { return category; }
    public void setCategory(String category) { this.category = category; }
    public boolean isMajor() { return major; }
    public void setMajor(boolean major) { this.major = major; }
    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }
}