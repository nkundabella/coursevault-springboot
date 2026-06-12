package com.springboot.coursevault.resource;

import com.springboot.coursevault.subject.Subject;

import com.springboot.coursevault.subject.Subject;

import jakarta.persistence.*;

@Entity
@Table(name = "resources")
public class Resource {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false)
    private String title;

    @Column(nullable = false)
    private String filePath;

    private int year;
    private int term;
    private String type; // NOTES, PAST_PAPER, etc.

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "subject_id")
    private Subject subject;

    @Column(name = "uploader_id")
    private Long uploaderId;

    @Column
    private String fileHash;

    public Resource() {}

    public Resource(Long id, String title, String filePath, int year, int term, String type, Subject subject, Long uploaderId) {
        this.id = id;
        this.title = title;
        this.filePath = filePath;
        this.year = year;
        this.term = term;
        this.type = type;
        this.subject = subject;
        this.uploaderId = uploaderId;
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

    public Subject getSubject() { return subject; }
    public void setSubject(Subject subject) { this.subject = subject; }

    public Long getUploaderId() { return uploaderId; }
    public void setUploaderId(Long uploaderId) { this.uploaderId = uploaderId; }

    public String getFileHash() { return fileHash; }
    public void setFileHash(String fileHash) { this.fileHash = fileHash; }
}