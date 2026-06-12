package com.springboot.coursevault.portal;

import com.springboot.coursevault.resource.ResourceDTO;

import com.springboot.coursevault.resource.ResourceDTO;

import java.util.List;

public class TimelineDTO {
    private List<ResourceDTO> recentResources;
    private List<Object> upcomingEvents;

    public List<ResourceDTO> getRecentResources() { return recentResources; }
    public void setRecentResources(List<ResourceDTO> recentResources) { this.recentResources = recentResources; }
    public List<Object> getUpcomingEvents() { return upcomingEvents; }
    public void setUpcomingEvents(List<Object> upcomingEvents) { this.upcomingEvents = upcomingEvents; }
}