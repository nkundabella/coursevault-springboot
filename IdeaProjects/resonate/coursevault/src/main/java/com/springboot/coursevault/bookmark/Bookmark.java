package com.springboot.coursevault.bookmark;

import com.springboot.coursevault.resource.Resource;

import jakarta.persistence.*;

@Entity
@Table(name = "bookmarks", uniqueConstraints = {
        @UniqueConstraint(columnNames = {"user_id", "resource_id"})
})
public class Bookmark {
    
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "user_id", nullable = false)
    private Long userId;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "resource_id", nullable = false)
    private Resource resource;

    public Bookmark() {}

    public Bookmark(Long userId, Resource resource) {
        this.userId = userId;
        this.resource = resource;
    }

    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }

    public Long getUserId() { return userId; }
    public void setUserId(Long userId) { this.userId = userId; }

    public Resource getResource() { return resource; }
    public void setResource(Resource resource) { this.resource = resource; }
}