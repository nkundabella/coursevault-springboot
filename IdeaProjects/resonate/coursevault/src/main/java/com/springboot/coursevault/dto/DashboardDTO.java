package com.springboot.coursevault.dto;

import java.util.List;

public class DashboardDTO {
    private long subjectCount;
    private long resourceCount;
    private long bookmarkCount;
    private List<ResourceDTO> recentResources;

    public long getSubjectCount() { return subjectCount; }
    public void setSubjectCount(long subjectCount) { this.subjectCount = subjectCount; }
    public long getResourceCount() { return resourceCount; }
    public void setResourceCount(long resourceCount) { this.resourceCount = resourceCount; }
    public long getBookmarkCount() { return bookmarkCount; }
    public void setBookmarkCount(long bookmarkCount) { this.bookmarkCount = bookmarkCount; }
    public List<ResourceDTO> getRecentResources() { return recentResources; }
    public void setRecentResources(List<ResourceDTO> recentResources) { this.recentResources = recentResources; }
}