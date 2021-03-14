SELECT name FROM people p 
INNER JOIN directors d ON d.person_id = p.id
INNER JOIN movies m ON m.id = d.movie_id
INNER JOIN ratings r ON r.movie_id = m.id
WHERE r.rating >= 9.0;