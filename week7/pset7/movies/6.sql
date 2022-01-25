-- Average rating of all movies released in 2012

SELECT AVG(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);

/* sqlite>
AVG(rating)
6.25052023121385