SELECT m.title FROM movies m 
INNER JOIN stars s ON s.movie_id = m.id
INNER JOIN people p ON s.person_id = p.id
WHERE p.name = 'Johnny Depp' AND m.title IN
(SELECT m.title FROM movies m 
INNER JOIN stars s ON s.movie_id = m.id
INNER JOIN people p ON s.person_id = p.id
WHERE p.name = 'Helena Bonham Carter');
