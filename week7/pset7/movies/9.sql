-- Names of all people starred in a movie in 2004
-- Ordered by birth year

SELECT DISTINCT people.name, people.birth FROM PEOPLE
    JOIN stars ON stars.person_id = people.id
    JOIN movies ON movies.id = stars.movie_id
WHERE movies.year = 2004
ORDER BY people.birth;

