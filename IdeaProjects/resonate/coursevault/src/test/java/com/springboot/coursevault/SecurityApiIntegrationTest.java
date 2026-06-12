package com.springboot.coursevault;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.test.web.servlet.MockMvc;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@SpringBootTest
@AutoConfigureMockMvc
class SecurityApiIntegrationTest {

    @Autowired
    private MockMvc mockMvc;

    @Test
    void downloadRequiresAuthentication() throws Exception {
        mockMvc.perform(get("/api/resources/1/download"))
                .andExpect(status().isForbidden());
    }

    @Test
    void adminEndpointsRequireAuthentication() throws Exception {
        mockMvc.perform(get("/api/admin/pending-teachers"))
                .andExpect(status().isForbidden());
    }

    @Test
    void calendarEventsRequireAuthentication() throws Exception {
        mockMvc.perform(get("/api/calendar/events"))
                .andExpect(status().isForbidden());
    }
}