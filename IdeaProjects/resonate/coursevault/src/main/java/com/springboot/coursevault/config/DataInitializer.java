package com.springboot.coursevault.config;

import com.springboot.coursevault.model.User;
import com.springboot.coursevault.repository.UserRepository;
import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class DataInitializer {

    @Bean
    CommandLineRunner initDatabase(UserRepository repository) {
        return args -> {
            // Default admin creation removed as per user request
        };
    }
}
