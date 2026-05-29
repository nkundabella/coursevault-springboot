package com.springboot.coursevault.controller;

import com.springboot.coursevault.dto.CalendarEventDTO;
import com.springboot.coursevault.dto.CreateCalendarEventRequest;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.service.CalendarService;
import com.springboot.coursevault.service.CurrentUserService;
import jakarta.validation.Valid;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/calendar")
public class CalendarController {

    private final CalendarService calendarService;
    private final CurrentUserService currentUserService;

    public CalendarController(CalendarService calendarService, CurrentUserService currentUserService) {
        this.calendarService = calendarService;
        this.currentUserService = currentUserService;
    }

    @GetMapping("/events")
    public ResponseEntity<List<CalendarEventDTO>> listEvents() {
        return ResponseEntity.ok(calendarService.getAllEvents());
    }

    @PostMapping("/events")
    public ResponseEntity<CalendarEventDTO> createEvent(@Valid @RequestBody CreateCalendarEventRequest request) {
        User user = currentUserService.requireCurrentUser();
        CalendarEventDTO created = calendarService.addEvent(request, user);
        return ResponseEntity.status(HttpStatus.CREATED).body(created);
    }

    @DeleteMapping("/events/{id}")
    public ResponseEntity<Void> deleteEvent(@PathVariable Long id) {
        User user = currentUserService.requireCurrentUser();
        calendarService.deleteEvent(id, user);
        return ResponseEntity.noContent().build();
    }
}