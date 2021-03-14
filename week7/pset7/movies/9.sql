SELECT name FROM people p 
INNER JOIN stars s ON s.person_id = p.id
INNER JOIN movies m ON m.id = s.movie_id
WHERE m.year = 2004 ORDER BY p.birth;