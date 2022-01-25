-- All movies from 2012 and their ratings ordered by rating (desc. order)
-- If equal rating movies get ordered alphabetical

SELECT movies.title, ratings.rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2012
ORDER BY rating DESC, title
/*LIMIT 20*/;