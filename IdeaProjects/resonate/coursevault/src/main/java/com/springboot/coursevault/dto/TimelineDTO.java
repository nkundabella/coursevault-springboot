package com.springboot.coursevault.dto;

import java.util.List;

public class TimelineDTO {
    private List<ResourceDTO> recentResources;
    private List<CalendarEventDTO> upcomingEvents;

    public List<ResourceDTO> getRecentResources() { return recentResources; }
    public void setRecentResources(List<ResourceDTO> recentResources) { this.recentResources = recentResources; }
    public List<CalendarEventDTO> getUpcomingEvents() { return upcomingEvents; }
    public void setUpcomingEvents(List<CalendarEventDTO> upcomingEvents) { this.upcomingEvents = upcomingEvents; }
}