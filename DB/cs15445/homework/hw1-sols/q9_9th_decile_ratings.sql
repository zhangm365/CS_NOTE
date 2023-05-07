-- For all people born in 1955, get their name and average rating on all
-- movies they have been part of through their careers. Output the 9th decile of
-- individuals as measured by their average career movie rating.

-- Detail:
-- Calculate average ratings for each individual born in 1955 across
-- only the *movies* they have been part of. Compute the quartiles for each
-- individual's average rating using NTILE.
-- (https://www.sqlitetutorial.net/sqlite-window-functions/sqlite-ntile/)
--
-- Make sure your output is formatted as follows (round average rating to
-- the nearest hundredth):
-- Stanley Nelson|7.13

WITH actors_and_movies_1955 AS (
     SELECT
          people.person_id,
          people.name,
          titles.title_id,
          titles.primary_title
     FROM
          people
     INNER JOIN
          crew ON people.person_id = crew.person_id
     INNER JOIN
          titles ON crew.title_id = titles.title_id
     WHERE people.born = 1955 AND titles.type = "movie"
),
actor_ratings AS (
     SELECT
          name,
          ROUND(AVG(ratings.rating), 2) as rating
     FROM ratings
     INNER JOIN actors_and_movies_1955 ON ratings.title_id = actors_and_movies_1955.title_id
     GROUP BY actors_and_movies_1955.person_id
),
quartiles AS (
     SELECT *, NTILE(10) OVER (ORDER BY rating ASC) AS RatingQuartile FROM actor_ratings
)
SELECT name, rating
FROM quartiles
WHERE RatingQuartile = 9
ORDER BY rating DESC, name ASC;

-- Topics: NTILE, more complicated joins, potential ctes

-- Answer:
-- Michiel Romeyn|7.3
-- Paula Anglin|7.3
-- Mani Ratnam|7.27
-- Charo Santos-Concio|7.25
-- Uri Gavriel|7.17
-- Marilou Diaz-Abaya|7.15
-- Stanley Nelson|7.13
-- Jeremiah S. Chechik|7.1
-- Marie Gruber|7.1
-- Ric Burns|7.1
-- Dana Carvey|7.05
-- Garry Bushell|7.05
-- Ildikó Enyedi|7.0
