package com.springboot.coursevault.portal;

import com.springboot.coursevault.user.CurrentUserService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
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