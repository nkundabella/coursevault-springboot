package com.springboot.coursevault.util;

public final class InputSanitizer {

    private InputSanitizer() {}

    public static String cleanText(String text, int maxLength) {
        if (text == null) {
            return "";
        }
        text = text.trim();
        if (text.length() > maxLength) {
            text = text.substring(0, maxLength);
        }
        // Store plain text; React escapes on render. Do not HTML-entity-encode API fields.
        return text;
    }

    public static String cleanIconClass(String iconClass) {
        if (iconClass == null || iconClass.isEmpty()) {
            return "fas fa-book";
        }
        return iconClass.replaceAll("[^a-zA-Z0-9 -]", "");
    }

    public static String cleanResourceType(String type) {
        if (type == null) {
            return "NOTES";
        }
        String upper = type.toUpperCase();
        return switch (upper) {
            case "PAST_PAPER", "GROUP_PRESENTATION", "OTHER" -> upper;
            default -> "NOTES";
        };
    }

    public static int parseIntInRange(String val, int min, int max, int defaultVal) {
        try {
            int parsed = Integer.parseInt(val);
            if (parsed < min || parsed > max) {
                return defaultVal;
            }
            return parsed;
        } catch (NumberFormatException e) {
            return defaultVal;
        }
    }
}
