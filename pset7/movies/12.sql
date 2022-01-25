-- Titles of all movies starring both Johnny Depp and Helena Bonham Carter

SELECT DISTINCT movies.title FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
WHERE (
    movies.id
    IN (
        SELECT stars.movie_id FROM stars
        WHERE stars.person_id
        IN (
            SELECT people.id FROM people
            WHERE people.name = 'Johnny Depp'
        )
    )
)
AND (
    movies.id
    IN (
        SELECT stars.movie_id FROM stars
        WHERE stars.person_id
        IN (
            SELECT people.id FROM people
            WHERE people.name = 'Helena Bonham Carter'
        )
    )
);



/* sqlite>
title
Corpse Bride
Charlie and the Chocolate Factory
Sweeney Todd: The Demon Barber of Fleet Street
Alice in Wonderland
Dark Shadows
Alice Through the Looking Glass