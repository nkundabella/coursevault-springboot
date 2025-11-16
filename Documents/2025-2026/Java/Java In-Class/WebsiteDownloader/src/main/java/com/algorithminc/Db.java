package com.algorithminc;

import java.sql.*;

public class Db {
    private Connection conn;

    public Db(String dbFile) throws SQLException {
        conn = DriverManager.getConnection("jdbc:sqlite:" + dbFile);
        createTables();
    }

    private void createTables() throws SQLException {
        String websiteTable = "CREATE TABLE IF NOT EXISTS website (" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                "website_name TEXT, " +
                "download_start_date_time TEXT, " +
                "download_end_date_time TEXT, " +
                "total_elapsed_time INTEGER, " +
                "total_downloaded_kilobytes INTEGER" +
                ")";
        
        String linkTable = "CREATE TABLE IF NOT EXISTS link (" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT, " + 
                "link_name TEXT, " + 
                "website_id INTEGER, " +
                "total_elapsed_time INTEGER, " +
                "total_downloaded_kilobytes INTEGER" +
                ")";
        
        Statement stmt = conn.createStatement();
        stmt.execute(websiteTable);
        stmt.execute(linkTable);
        stmt.close();
    }

    public int insertWebsiteRecord(String name, String start, String end, long elapsed, long kb) 
            throws SQLException {
        String sql = "INSERT INTO website(website_name, download_start_date_time, " +
                "download_end_date_time, total_elapsed_time, total_downloaded_kilobytes) " +
                "VALUES(?,?,?,?,?)";
        
        PreparedStatement pstmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
        pstmt.setString(1, name);
        pstmt.setString(2, start);
        pstmt.setString(3, end);
        pstmt.setLong(4, elapsed);
        pstmt.setLong(5, kb);
        pstmt.executeUpdate();
        
        ResultSet rs = pstmt.getGeneratedKeys();
        int id = -1;
        if (rs.next()) {
            id = rs.getInt(1);
        }
        rs.close();
        pstmt.close();
        return id;
    }

    public void updateWebsiteRecord(int id, String end, long elapsed, long kb) throws SQLException {
        String sql = "UPDATE website SET download_end_date_time=?, total_elapsed_time=?, " +
                "total_downloaded_kilobytes=? WHERE id=?";
        
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, end);
        pstmt.setLong(2, elapsed);
        pstmt.setLong(3, kb);
        pstmt.setInt(4, id);
        pstmt.executeUpdate();
        pstmt.close();
    }

    public void insertLinkRecord(String link, int websiteId, long elapsed, long kb) 
            throws SQLException {
        String sql = "INSERT INTO link(link_name, website_id, total_elapsed_time, " +
                "total_downloaded_kilobytes) VALUES(?,?,?,?)";
        
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, link);
        pstmt.setInt(2, websiteId);
        pstmt.setLong(3, elapsed);
        pstmt.setLong(4, kb);
        pstmt.executeUpdate();
        pstmt.close();
    }

    public void close() throws SQLException {
        if (conn != null) {
            conn.close();
        }
    }
}
