package com.algorithminc;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Website Downloader");
        System.out.println("==================\n");
        
        System.out.print("Enter website URL: ");
        String url = scanner.nextLine().trim();
        
        if (!url.startsWith("http://") && !url.startsWith("https://")) {
            System.out.println("Error: URL must start with http:// or https://");
            return;
        }
        
        System.out.print("Enter output directory (press Enter for current): ");
        String dir = scanner.nextLine().trim();
        Path outputDir = dir.isEmpty() ? Paths.get(".") : Paths.get(dir);
        
        try {
            WebsiteDownloader downloader = new WebsiteDownloader(url, outputDir);
            downloader.run();
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
        
        scanner.close();
    }
}