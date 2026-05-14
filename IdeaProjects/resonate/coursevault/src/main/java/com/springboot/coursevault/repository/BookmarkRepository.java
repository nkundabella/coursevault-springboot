package com.springboot.coursevault.repository;

import com.springboot.coursevault.model.Bookmark;
import com.springboot.coursevault.model.Resource;
import com.springboot.coursevault.model.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface BookmarkRepository extends JpaRepository<Bookmark, Long> {
    List<Bookmark> findByUser(User user);
    Optional<Bookmark> findByUserAndResource(User user, Resource resource);
    void deleteByUserAndResource(User user, Resource resource);
}