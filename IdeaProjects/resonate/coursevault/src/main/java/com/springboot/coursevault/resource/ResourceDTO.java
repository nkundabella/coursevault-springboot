package com.springboot.coursevault.resource;

public class ResourceDTO {
    private Long id;
    private String title;
    private String fileName;
    private String downloadUrl;
    private int year;
    private int term;
    private String type;
    private Long uploaderId;
    private String uploaderName;
    private Long subjectId;
    private String subjectName;

    public ResourceDTO() {}

    public ResourceDTO(Long id, String title, String fileName, String downloadUrl,
                       int year, int term, String type, Long uploaderId, String uploaderName,
                       Long subjectId, String subjectName) {
        this.id = id;
        this.title = title;
        this.fileName = fileName;
        this.downloadUrl = downloadUrl;
        this.year = year;
        this.term = term;
        this.type = type;
        this.uploaderId = uploaderId;
        this.uploaderName = uploaderName;
        this.subjectId = subjectId;
        this.subjectName = subjectName;
    }

    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }

    public String getFileName() { return fileName; }
    public void setFileName(String fileName) { this.fileName = fileName; }

    public String getDownloadUrl() { return downloadUrl; }
    public void setDownloadUrl(String downloadUrl) { this.downloadUrl = downloadUrl; }

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

    public Long getSubjectId() { return subjectId; }
    public void setSubjectId(Long subjectId) { this.subjectId = subjectId; }

    public String getSubjectName() { return subjectName; }
    public void setSubjectName(String subjectName) { this.subjectName = subjectName; }
}
