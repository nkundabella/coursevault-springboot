package com.springboot.coursevault.dto;

public class AdminStatsDTO {
    private long totalUsers;
    private long adminCount;
    private long teacherCount;
    private long studentCount;
    private long pendingTeacherCount;

    public long getTotalUsers() { return totalUsers; }
    public void setTotalUsers(long totalUsers) { this.totalUsers = totalUsers; }
    public long getAdminCount() { return adminCount; }
    public void setAdminCount(long adminCount) { this.adminCount = adminCount; }
    public long getTeacherCount() { return teacherCount; }
    public void setTeacherCount(long teacherCount) { this.teacherCount = teacherCount; }
    public long getStudentCount() { return studentCount; }
    public void setStudentCount(long studentCount) { this.studentCount = studentCount; }
    public long getPendingTeacherCount() { return pendingTeacherCount; }
    public void setPendingTeacherCount(long pendingTeacherCount) { this.pendingTeacherCount = pendingTeacherCount; }
}