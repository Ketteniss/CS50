-- All people who starred in 'Toy Story'

SELECT DISTINCT people.name FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
WHERE people.id
    IN (
        SELECT stars.person_id FROM stars
        WHERE stars.movie_id
            IN (
                SELECT movies.id FROM movies
                WHERE title = 'Toy Story'
                )
        );

/* sqlite>
name
Don Rickles
Tom Hanks
Jim Varney
Tim Allen