package com.algorithminc;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URI;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class WebsiteDownloader {
    private URI baseUri;
    private Path baseDir;
    private Db db;
    private String domainName;

    public WebsiteDownloader(String url, Path outputBase) throws Exception {
        this.baseUri = new URI(url);
        String domain = baseUri.getHost();
        if (domain == null) {
            throw new Exception("Invalid URL");
        }
        
        this.domainName = domain.replace("www.", "");
        this.baseDir = outputBase.resolve(domainName);
        Files.createDirectories(baseDir);
        
        Path dbPath = outputBase.resolve("downloads.db");
        this.db = new Db(dbPath.toString());
    }

    public void run() throws Exception {
        System.out.println("\nStarting download: " + baseUri);
        
        Instant start = Instant.now();
        long totalBytes = 0;

        // Download homepage
        System.out.println("Downloading homepage...");
        Path homeFile = downloadFile(baseUri.toURL(), "index.html");
        totalBytes += Files.size(homeFile);

        // Extract links
        System.out.println("Extracting links...");
        List<URI> links = extractLinks(homeFile);
        System.out.println("Found " + links.size() + " links:");
        for (URI link : links) {
            System.out.println("  - " + link);
        }

        // Save to database
        int websiteId = db.insertWebsiteRecord(domainName, start.toString(), null, 0, 0);

        // Download each link
        System.out.println("\nDownloading links...");
        for (URI link : links) {
            System.out.print("Downloading " + link + "... ");
            Instant linkStart = Instant.now();
            
            Path file = downloadFile(link.toURL(), null);
            if (file != null) {
                long size = Files.size(file);
                Instant linkEnd = Instant.now();
                long elapsed = Duration.between(linkStart, linkEnd).toMillis();
                long kb = size / 1024;
                
                System.out.println(kb + " KB in " + elapsed + " ms");
                db.insertLinkRecord(link.toString(), websiteId, elapsed, kb);
                totalBytes += size;
            } else {
                System.out.println("failed");
            }
        }

        // Update database
        Instant end = Instant.now();
        long totalElapsed = Duration.between(start, end).toMillis();
        long totalKb = totalBytes / 1024;
        db.updateWebsiteRecord(websiteId, end.toString(), totalElapsed, totalKb);

        // Print report
        System.out.println("\n=== Download Complete ===");
        System.out.println("Website: " + domainName);
        System.out.println("Start: " + start);
        System.out.println("End: " + end);
        System.out.println("Total time: " + totalElapsed + " ms");
        System.out.println("Total size: " + totalKb + " KB");
        System.out.println("Report saved to database");

        db.close();
    }

    private Path downloadFile(URL url, String defaultName) {
        try {
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestProperty("User-Agent", "Mozilla/5.0");
            
            int response = conn.getResponseCode();
            if (response >= 400) {
                return null;
            }

            // Get filename
            String path = url.getPath();
            String fileName;
            if (defaultName != null) {
                fileName = defaultName;
            } else if (path.isEmpty() || path.equals("/")) {
                fileName = "index.html";
            } else {
                fileName = Paths.get(path).getFileName().toString();
                if (fileName.isEmpty()) {
                    fileName = "index.html";
                }
            }

            // Save file
            String relativePath = path.replaceFirst("^/", "");
            if (relativePath.isEmpty() || relativePath.equals("/")) {
                relativePath = fileName;
            } else if (!relativePath.contains(".")) {
                relativePath = relativePath + "/" + fileName;
            }

            Path outPath = baseDir.resolve(relativePath);
            Files.createDirectories(outPath.getParent());

            // Download
            try (InputStream in = conn.getInputStream(); 
                 OutputStream out = Files.newOutputStream(outPath)) {
                byte[] buf = new byte[8192];
                int read;
                long total = 0;
                while ((read = in.read(buf)) != -1) {
                    out.write(buf, 0, read);
                    total += read;
                }
            }

            return outPath;
        } catch (Exception e) {
            return null;
        }
    }

    private List<URI> extractLinks(Path htmlFile) {
        Set<URI> seen = new HashSet<>();
        List<URI> result = new ArrayList<>();
        
        try {
            Document doc = Jsoup.parse(htmlFile.toFile(), "UTF-8", baseUri.toString());
            Elements links = doc.select("a[href]");
            
            for (Element link : links) {
                String href = link.attr("abs:href");
                if (href == null || href.isEmpty()) continue;
                
                try {
                    URI uri = new URI(href);
                    if (uri.getHost() != null && uri.getHost().equals(baseUri.getHost())) {
                        URI clean = new URI(uri.getScheme(), uri.getAuthority(), 
                                uri.getPath(), uri.getQuery(), null);
                        if (!seen.contains(clean)) {
                            seen.add(clean);
                            result.add(clean);
                        }
                    }
                } catch (Exception e) {
                    // skip invalid URLs
                }
            }
        } catch (Exception e) {
            System.out.println("Error parsing HTML: " + e.getMessage());
        }
        
        return result;
    }
}