package com.springboot.coursevault.portal;

public class SystemConfigDTO {
    private Long id;
    private String smtpHost;
    private String smtpPort;
    private String smtpUser;
    private boolean smtpPasswordConfigured;

    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }
    public String getSmtpHost() { return smtpHost; }
    public void setSmtpHost(String smtpHost) { this.smtpHost = smtpHost; }
    public String getSmtpPort() { return smtpPort; }
    public void setSmtpPort(String smtpPort) { this.smtpPort = smtpPort; }
    public String getSmtpUser() { return smtpUser; }
    public void setSmtpUser(String smtpUser) { this.smtpUser = smtpUser; }
    public boolean isSmtpPasswordConfigured() { return smtpPasswordConfigured; }
    public void setSmtpPasswordConfigured(boolean smtpPasswordConfigured) { this.smtpPasswordConfigured = smtpPasswordConfigured; }
}