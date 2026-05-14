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
            if (repository.count() == 0) {
                User admin = new User();
                admin.setFullName("Admin User");
                admin.setEmail("admin@coursevault.com");
                admin.setPassword("admin123");
                admin.setRole("ADMIN");
                repository.save(admin);
                System.out.println("Seeded database with default admin: admin@coursevault.com (ID: " + admin.getId() + ")");
            }
        };
    }
}
