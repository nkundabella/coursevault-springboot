package com.springboot.coursevault.service;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;

@Service
public class CaptchaService {

    // Cloudflare Turnstile always-pass test secret key.
    // Replace with your real secret key from https://dash.cloudflare.com/ when in production.
    @Value("${captcha.secret-key:1x0000000000000000000000000000000AA}")
    private String secretKey;

    private final HttpClient httpClient = HttpClient.newBuilder()
            .connectTimeout(Duration.ofSeconds(10))
            .build();

    /**
     * Verifies a Cloudflare Turnstile CAPTCHA token.
     * @param token  The token submitted by the user from the frontend.
     * @param ip     The user's IP address (from the request).
     * @return true if the CAPTCHA is valid, false otherwise.
     */
    public boolean verify(String token, String ip) {
        if (token == null || token.isBlank()) return false;

        try {
            String params = "secret=" + secretKey + "&response=" + token + "&remoteip=" + ip;

            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create("https://challenges.cloudflare.com/turnstile/v0/siteverify"))
                    .header("Content-Type", "application/x-www-form-urlencoded")
                    .POST(HttpRequest.BodyPublishers.ofString(params))
                    .build();

            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());
            return response.body().contains("\"success\":true");
        } catch (Exception e) {
            System.err.println("[CaptchaService] Verification failed: " + e.getMessage());
            return false;
        }
    }
}
