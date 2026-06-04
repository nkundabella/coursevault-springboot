package com.springboot.coursevault.service;

import com.springboot.coursevault.config.OfficialAcademicCalendar2025_2026;
import com.springboot.coursevault.dto.CalendarEventDTO;
import com.springboot.coursevault.dto.CreateCalendarEventRequest;
import com.springboot.coursevault.exception.GlobalExceptionHandler;
import com.springboot.coursevault.model.CalendarEvent;
import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.CalendarEventRepository;
import com.springboot.coursevault.security.AuthorizationService;
import com.springboot.coursevault.util.InputSanitizer;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.stream.Collectors;

@Service
public class CalendarService {

    private final CalendarEventRepository calendarEventRepository;
    private final AuthorizationService authorizationService;

    public CalendarService(CalendarEventRepository calendarEventRepository,
                           AuthorizationService authorizationService) {
        this.calendarEventRepository = calendarEventRepository;
        this.authorizationService = authorizationService;
    }

    @Transactional
    public List<CalendarEventDTO> getAllEvents() {
        ensureOfficialCalendar();
        return calendarEventRepository.findAllByOrderByDateAsc().stream()
                .map(this::toDto)
                .collect(Collectors.toList());
    }

    @Transactional
    public CalendarEventDTO addEvent(CreateCalendarEventRequest request, User user) {
        authorizationService.assertAdminOrTeacher(user);

        CalendarEvent event = new CalendarEvent();
        event.setTitle(InputSanitizer.cleanText(request.getTitle(), 150));
        event.setDate(request.getDate());
        event.setTerm(request.getTerm() != null ? request.getTerm() : 1);
        event.setCategory(InputSanitizer.cleanText(request.getCategory(), 50));
        event.setMajor(request.isMajor());
        event.setDescription(InputSanitizer.cleanText(request.getDescription(), 500));
        event.setUserId(user.getId());
        return toDto(calendarEventRepository.save(event));
    }

    @Transactional
    public void deleteEvent(Long id, User user) {
        authorizationService.assertAdminOrTeacher(user);
        CalendarEvent event = calendarEventRepository.findById(id)
                .orElseThrow(() -> GlobalExceptionHandler.notFound("Event not found"));
        calendarEventRepository.delete(event);
    }

    private CalendarEventDTO toDto(CalendarEvent event) {
        return new CalendarEventDTO(
                event.getId(), event.getTitle(), event.getDate(), event.getTerm(),
                event.getCategory(), event.isMajor(), event.getDescription());
    }

    private void ensureOfficialCalendar() {
        if (calendarEventRepository.existsByTitle(OfficialAcademicCalendar2025_2026.MARKER_TITLE)) {
            return;
        }
        calendarEventRepository.deleteAll();
        calendarEventRepository.saveAll(OfficialAcademicCalendar2025_2026.buildEvents());
    }
}