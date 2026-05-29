package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.DashboardDTO;
import com.springboot.coursevault.dto.TimelineDTO;
import com.springboot.coursevault.service.CurrentUserService;
import com.springboot.coursevault.service.DashboardService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class NavigationController {

    private final DashboardService dashboardService;
    private final CurrentUserService currentUserService;

    public NavigationController(DashboardService dashboardService, CurrentUserService currentUserService) {
        this.dashboardService = dashboardService;
        this.currentUserService = currentUserService;
    }

    @GetMapping("/api/dashboard")
    public ResponseEntity<DashboardDTO> dashboard() {
        return ResponseEntity.ok(dashboardService.getDashboard(currentUserService.requireCurrentUser()));
    }

    @GetMapping("/api/timeline")
    public ResponseEntity<TimelineDTO> timeline() {
        return ResponseEntity.ok(dashboardService.getTimeline());
    }
}