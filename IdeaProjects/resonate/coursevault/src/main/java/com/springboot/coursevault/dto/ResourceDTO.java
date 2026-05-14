package com.springboot.coursevault.dto;

public class ResourceDTO {
    private Long id;
    private String title;
    private String filePath;
    private int year;
    private int term;
    private String type;
    private Long uploaderId;
    private String uploaderName;

    public ResourceDTO() {}

    public ResourceDTO(Long id, String title, String filePath, int year, int term, String type, Long uploaderId, String uploaderName) {
        this.id = id;
        this.title = title;
        this.filePath = filePath;
        this.year = year;
        this.term = term;
        this.type = type;
        this.uploaderId = uploaderId;
        this.uploaderName = uploaderName;
    }

    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }

    public String getFilePath() { return filePath; }
    public void setFilePath(String filePath) { this.filePath = filePath; }

    public int getYear() { return year; }
    public void setYear(int year) { this.year = year; }

    public int getTerm() { return term; }
    public void setTerm(int term) { this.term = term; }

    public String getType() { return type; }
    public void setType(String type) { this.type = type; }

    public Long getUploaderId() { return uploaderId; }
    public void setUploaderId(Long uploaderId) { this.uploaderId = uploaderId; }

    public String getUploaderName() { return uploaderName; }
    public void setUploaderName(String uploaderName) { this.uploaderName = uploaderName; }
}