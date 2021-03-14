SELECT title FROM movies m 
INNER JOIN stars s ON s.movie_id = m.id
INNER JOIN people p ON s.person_id = p.id
INNER JOIN ratings r ON m.id = r.movie_id
WHERE p.name = 'Chadwick Boseman'
ORDER BY r.rating DESC LIMIT 5;