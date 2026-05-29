package com.springboot.coursevault.service;

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

import java.time.LocalDate;
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

    @Transactional(readOnly = true)
    public List<CalendarEventDTO> getAllEvents() {
        List<CalendarEvent> events = calendarEventRepository.findAllByOrderByDateAsc();
        if (events.isEmpty()) {
            seedDefaults();
            events = calendarEventRepository.findAllByOrderByDateAsc();
        }
        return events.stream().map(this::toDto).collect(Collectors.toList());
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
        event.setUser(user);
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

    private void seedDefaults() {
        String[][] defaults = {
            {"Orientation Week", "2025-09-01", "1", "General", "true", "Welcome to the new academic year!"},
            {"Mid-Term Assessments", "2025-10-20", "1", "Exam", "true", "First major assessment block for Term 1."},
            {"End of Term 1 Exams", "2025-12-12", "1", "Finals", "true", "Concluding exams for the first term."},
            {"Start of Term 2", "2026-01-12", "2", "General", "false", "Resuming classes for the second half of the year."},
            {"Easter Break Begins", "2026-04-03", "2", "Holiday", "false", "Spring break for all students and staff."},
            {"Final Year Project Submission", "2026-05-15", "3", "Major", "true", "Deadline for all final year undergraduate projects."},
            {"Promotional Exams", "2026-06-22", "3", "Finals", "true", "Year-end promotional examinations."}
        };

        for (String[] d : defaults) {
            CalendarEvent e = new CalendarEvent();
            e.setTitle(d[0]);
            e.setDate(LocalDate.parse(d[1]));
            e.setTerm(Integer.parseInt(d[2]));
            e.setCategory(d[3]);
            e.setMajor(Boolean.parseBoolean(d[4]));
            e.setDescription(d[5]);
            calendarEventRepository.save(e);
        }
    }
}