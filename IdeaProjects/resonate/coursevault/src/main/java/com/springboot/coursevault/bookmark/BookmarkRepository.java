package com.springboot.coursevault.bookmark;

import com.springboot.coursevault.resource.Resource;

import com.springboot.coursevault.bookmark.Bookmark;
import com.springboot.coursevault.resource.Resource;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface BookmarkRepository extends JpaRepository<Bookmark, Long> {
    List<Bookmark> findByUserId(Long userId);
    Optional<Bookmark> findByUserIdAndResource(Long userId, Resource resource);
    void deleteByUserIdAndResource(Long userId, Resource resource);
    void deleteByResource(Resource resource);
}