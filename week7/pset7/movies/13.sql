SELECT DISTINCT name FROM people p 
INNER JOIN stars s ON s.person_id = p.id
INNER JOIN movies m ON m.id = s.movie_id
WHERE m.title IN
(SELECT DISTINCT title FROM movies m 
INNER JOIN stars s ON s.movie_id = m.id
INNER JOIN people p ON p.id = s.person_id
WHERE p.name = 'Kevin Bacon' AND p.birth = 1958)
AND p.name != 'Kevin Bacon' AND p.birth != 1958;