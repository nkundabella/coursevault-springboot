package com.springboot.coursevault.service;

import com.springboot.coursevault.dto.DashboardDTO;
import com.springboot.coursevault.dto.TimelineDTO;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.BookmarkRepository;
import com.springboot.coursevault.repository.ResourceRepository;
import com.springboot.coursevault.repository.SubjectRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Collections;

@Service
public class DashboardService {

    private final SubjectRepository subjectRepository;
    private final ResourceRepository resourceRepository;
    private final BookmarkRepository bookmarkRepository;
    private final ResourceService resourceService;

    public DashboardService(SubjectRepository subjectRepository,
                            ResourceRepository resourceRepository,
                            BookmarkRepository bookmarkRepository,
                            ResourceService resourceService) {
        this.subjectRepository = subjectRepository;
        this.resourceRepository = resourceRepository;
        this.bookmarkRepository = bookmarkRepository;
        this.resourceService = resourceService;
    }

    @Transactional(readOnly = true)
    public DashboardDTO getDashboard(User user) {
        DashboardDTO dto = new DashboardDTO();
        dto.setSubjectCount(subjectRepository.count());
        dto.setResourceCount(resourceRepository.count());
        dto.setBookmarkCount(bookmarkRepository.findByUserId(user.getId()).size());
        dto.setRecentResources(resourceService.getRecentResources(3));
        return dto;
    }

    @Transactional(readOnly = true)
    public TimelineDTO getTimeline() {
        TimelineDTO dto = new TimelineDTO();
        dto.setRecentResources(resourceService.getRecentResources(10));
        dto.setUpcomingEvents(Collections.emptyList());
        return dto;
    }
}