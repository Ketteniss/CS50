-- Names of all directors with movie ratings of 9.0 or higher

SELECT DISTINCT people.name FROM people
    JOIN directors ON directors.person_id = people.id
    JOIN movies ON movies.id = directors.movie_id
    JOIN ratings ON ratings.movie_id = movies.id
WHERE rating >= 9.0
/* LIMIT 10 */;

/* sqlite>
name
Francis Ford Coppola
John D. Goodell
Moustapha Akkad
György Révész
Joaquín Hidalgo
Slobodan Sijan
Allen Rosen
Ludmil Staikov
Christian Baudissin
Michael Glawogger