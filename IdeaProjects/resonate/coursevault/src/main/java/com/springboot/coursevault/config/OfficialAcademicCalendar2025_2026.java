package com.springboot.coursevault.config;

import com.springboot.coursevault.model.CalendarEvent;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;


public final class OfficialAcademicCalendar2025_2026 {

    public static final String MARKER_TITLE = "Start of Classes & Induction Week";

    private OfficialAcademicCalendar2025_2026() {}

    public static List<CalendarEvent> buildEvents() {
        List<CalendarEvent> events = new ArrayList<>();
        for (String[] row : ROWS) {
            CalendarEvent e = new CalendarEvent();
            e.setTitle(row[0]);
            e.setDate(LocalDate.parse(row[1]));
            e.setTerm(Integer.parseInt(row[2]));
            e.setCategory(row[3]);
            e.setMajor(Boolean.parseBoolean(row[4]));
            e.setDescription(row[5]);
            events.add(e);
        }
        return events;
    }

    private static final String[][] ROWS = {
        // Term 1
        {"Start of Classes & Induction Week", "2025-09-08", "1", "Academic", "true",
            "Orientation and registration of freshers and clubs exhibition."},
        {"Classes Start for Freshers", "2025-09-15", "1", "Academic", "false",
            "Classes begin for first-year students."},
        {"Call for Student-Led Projects (4th Hackathon)", "2025-10-05", "1", "Event", "true",
            "Call for initiation of student-led projects."},
        {"3rd Hackathon", "2025-10-15", "1", "Event", "true", "Third hackathon event."},
        {"Mentorship Report Submission", "2025-10-31", "1", "Deadline", "false",
            "Submission of students' mentorship report."},
        {"Continuous Assessment Tests (CAT)", "2025-11-03", "1", "Exam", "true",
            "Continuous assessment tests (3-7 November)."},
        {"CAT Feedback to Students", "2025-11-14", "1", "Academic", "false",
            "Submission of CAT feedback to students."},
        {"Project Ideation Presentation", "2025-11-24", "1", "Event", "true",
            "Project ideation presentation (24-25 November)."},
        {"Mentorship Report Submission", "2025-12-05", "1", "Deadline", "false",
            "Submission of students' mentorship report."},
        {"Final Exams Start (Term 1)", "2025-12-08", "1", "Exam", "true", "Term 1 final examinations begin."},
        {"Final Exams End (Term 1)", "2025-12-15", "1", "Exam", "true", "Term 1 final examinations end."},
        {"End Term One Results Submission", "2025-12-17", "1", "Deadline", "false",
            "Submission of end of Term 1 results."},
        {"Christmas Break", "2025-12-22", "1", "Holidays", "true",
            "Christmas break (22 December 2025 - 4 January 2026)."},

        // Term 2
        {"School Reopening", "2026-01-04", "2", "Academic", "true", "School reopens after Christmas break."},
        {"Start of Classes (Term 2)", "2026-01-05", "2", "Academic", "true", "Start of Term 2 classes."},
        {"National Heroes Day", "2026-02-01", "2", "Holidays", "true", "National Heroes Day."},
        {"Mentorship Report Submission", "2026-02-13", "2", "Deadline", "false",
            "Submission of students' mentorship report."},
        {"Continuous Assessment Tests (CAT)", "2026-02-15", "2", "Exam", "true",
            "Continuous assessment tests (15-21 February)."},
        {"CAT Feedback to Students", "2026-02-25", "2", "Academic", "false",
            "Submission of CAT feedback to students."},
        {"Presentation of the First Prototype", "2026-02-25", "2", "Event", "true",
            "Presentation of the first prototype (25-26 February)."},
        {"Mentorship Report Submission", "2026-03-20", "2", "Deadline", "false",
            "Submission of students' mentorship report."},
        {"Final Exams Start (Term 2)", "2026-03-25", "2", "Exam", "true", "Term 2 final examinations begin."},
        {"Final Exams End (Term 2)", "2026-03-31", "2", "Exam", "true", "Term 2 final examinations end."},

        // Term 3
        {"End Term Two Results Submission", "2026-04-02", "3", "Deadline", "false",
            "Submission of end of Term 2 results."},
        {"Genocide Memorial Week", "2026-04-07", "3", "Event", "true",
            "Genocide memorial week (7-13 April)."},
        {"End Term Two Break", "2026-04-12", "3", "Holidays", "true", "End of Term 2 break."},
        {"School Reopening (Term 3)", "2026-04-19", "3", "Academic", "true", "School reopens for Term 3."},
        {"Start of Classes (Term 3)", "2026-04-20", "3", "Academic", "true", "Start of Term 3 classes."},
        {"Labor Day", "2026-05-01", "3", "Holidays", "true", "Labor Day public holiday."},
        {"Mentorship Report Submission", "2026-05-07", "3", "Deadline", "false",
            "Submission of students' mentorship report."},
        {"Visit of a Genocide Memorial", "2026-05-08", "3", "Event", "false", "Visit of a genocide memorial site."},
        {"Continuous Assessment Tests (CAT)", "2026-05-11", "3", "Exam", "true",
            "Continuous assessment tests (11-15 May)."},
        {"CAT Feedback to Students", "2026-05-22", "3", "Academic", "false",
            "Submission of CAT feedback to students."},
        {"Final Prototype Presentation (4th Hackathon)", "2026-05-27", "3", "Event", "true",
            "Presentation of the final prototype - final assessment (27-28 May)."},
        {"Hackathon Preparation Phase", "2026-05-29", "3", "Event", "false",
            "Finalizing prototypes for the 4th Hackathon."},
        {"NESA Practical Examinations Start", "2026-06-01", "3", "Exam", "true",
            "NESA practical examinations begin."},
        {"Mentorship Report Submission", "2026-06-12", "3", "Deadline", "false",
            "Submission of students' mentorship report."},
        {"Final Exams Start (Term 3)", "2026-06-15", "3", "Exam", "true", "Term 3 final examinations begin."},
        {"NESA Practical Examinations End", "2026-06-19", "3", "Exam", "true",
            "NESA practical examinations end."},
        {"Final Exams End (Term 3)", "2026-06-22", "3", "Exam", "true", "Term 3 final examinations end."},
        {"End of Term 3 Results Submission", "2026-06-25", "3", "Deadline", "false",
            "Submission of end of Term 3 results."},
        {"Independence Day", "2026-07-01", "3", "Holidays", "true", "Independence Day."},
        {"End of School Year", "2026-07-03", "3", "Academic", "true", "End of school year."},
        {"Liberation Day", "2026-07-04", "3", "Holidays", "true", "Liberation Day."},
        {"NESA Theoretical Examinations Start", "2026-07-15", "3", "Exam", "true",
            "NESA theoretical examinations begin."},
        {"NESA Theoretical Examinations End", "2026-07-24", "3", "Exam", "true",
            "NESA theoretical examinations end."},
        {"Ideation and Prototyping / Internship Start", "2026-08-01", "3", "Academic", "true",
            "Ideation and prototyping; start of internship for finalists."},
        {"Vacation", "2026-08-16", "3", "Holidays", "true", "Vacation period."},
        {"Second Sitting Exams", "2026-08-23", "3", "Exam", "true", "Second sitting examinations."},
    };
}