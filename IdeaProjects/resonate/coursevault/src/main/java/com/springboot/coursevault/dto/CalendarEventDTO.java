package com.springboot.coursevault.dto;

import java.time.LocalDate;

public class CalendarEventDTO {
    private Long id;
    private String title;
    private LocalDate date;
    private Integer term;
    private String category;
    private boolean major;
    private String description;

    public CalendarEventDTO() {}

    public CalendarEventDTO(Long id, String title, LocalDate date, Integer term,
                            String category, boolean major, String description) {
        this.id = id;
        this.title = title;
        this.date = date;
        this.term = term;
        this.category = category;
        this.major = major;
        this.description = description;
    }

    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }
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