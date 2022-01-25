-- 5 highest rated movies starring Chadwick Boseman desc. order

SELECT DISTINCT movies.title FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN ratings ON ratings.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
WHERE people.name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;

/* sqlite>
title
42
Black Panther
Marshall
Get on Up
Draft Day