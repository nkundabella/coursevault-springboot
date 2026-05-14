package com.springboot.coursevault.repository;

import com.springboot.coursevault.model.VerificationCode;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface VerificationCodeRepository extends JpaRepository<VerificationCode, Long> {
    Optional<VerificationCode> findByEmailAndCodeAndType(String email, String code, String type);
    void deleteByEmailAndType(String email, String type);
}
