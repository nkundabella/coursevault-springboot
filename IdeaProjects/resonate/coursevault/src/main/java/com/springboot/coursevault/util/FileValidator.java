package com.springboot.coursevault.util;

import java.io.IOException;
import java.io.InputStream;

public class FileValidator {

    private static final byte[] PDF_MAGIC = {0x25, 0x50, 0x44, 0x46}; // %PDF
    private static final byte[] PNG_MAGIC = {(byte)0x89, 0x50, 0x4E, 0x47};
    private static final byte[] JPEG_MAGIC_1 = {(byte)0xFF, (byte)0xD8, (byte)0xFF};
    private static final byte[] ZIP_MAGIC = {0x50, 0x4B, 0x03, 0x04}; // docx, xlsx, pptx
    private static final byte[] OLE2_MAGIC = {(byte)0xD0, (byte)0xCF, (byte)0x11, (byte)0xE0, (byte)0xA1, (byte)0xB1, 0x1A, (byte)0xE1}; // doc, xls, ppt
    
    private static final byte[] EXE_MAGIC = {0x4D, 0x5A}; // MZ
    private static final byte[] ELF_MAGIC = {0x7F, 0x45, 0x4C, 0x46}; // .ELF

    public static boolean isSafeAndValid(InputStream is, String extension) throws IOException {
        byte[] header = new byte[8];
        int bytesRead = is.read(header);
        
        if (bytesRead < 2) {
            return "txt".equals(extension) || "csv".equals(extension);
        }

        switch (extension.toLowerCase()) {
            case "pdf":
                return matchesValidSignature(header, PDF_MAGIC);
            case "png":
                return matchesValidSignature(header, PNG_MAGIC);
            case "jpg":
            case "jpeg":
                return matchesValidSignature(header, JPEG_MAGIC_1);
            case "docx":
            case "xlsx":
            case "pptx":
                return matchesValidSignature(header, ZIP_MAGIC);
            case "doc":
            case "xls":
            case "ppt":
                return matchesValidSignature(header, OLE2_MAGIC);
            case "txt":
            case "csv":
                if (matchesValidSignature(header, EXE_MAGIC) || 
                    matchesValidSignature(header, ELF_MAGIC) || 
                    matchesValidSignature(header, PDF_MAGIC) || 
                    matchesValidSignature(header, ZIP_MAGIC) || 
                    matchesValidSignature(header, PNG_MAGIC) || 
                    matchesValidSignature(header, OLE2_MAGIC)) {
                    return false;
                }
                return true;
            default:
                return false;
        }
    }

    private static boolean matchesValidSignature(byte[] fileHeader, byte[] magicNumber) {
        if (fileHeader == null || fileHeader.length < magicNumber.length) return false;
        for (int i = 0; i < magicNumber.length; i++) {
            if (fileHeader[i] != magicNumber[i]) return false;
        }
        return true;
    }
}
