-- Determine the most popular works with a person who has "Cruise" in their
-- name and is born in 1962.

-- Detail:
-- Get the works with the most votes that have a person in the crew
-- with "Cruise" in their name who was born in 1962. Return both the name of the
-- work and the number of votes and only list the top 10 results.

-- Option 1
-- Run Time: real 3.833 user 3.460795 sys 0.355109
WITH cruise_movies AS (
     SELECT
          crew.title_id AS title_id
     FROM crew
     INNER JOIN
          people ON crew.person_id = people.person_id
     WHERE people.name LIKE "%Cruise%" AND people.born = 1962
)
SELECT
     titles.primary_title as name,
     ratings.votes as votes
FROM
     cruise_movies
INNER JOIN
     ratings ON cruise_movies.title_id = ratings.title_id
INNER JOIN
     titles ON cruise_movies.title_id = titles.title_id
ORDER BY votes DESC
LIMIT 10;

-- Option 2
-- (commented out so solution can be verified with Gradescope, otherwise will
-- duplicate results)
-- Run Time: real 7.916 user 5.712018 sys 1.163099
-- SELECT
--      titles.primary_title AS name,
--      ratings.votes AS votes
-- FROM
--      titles
-- INNER JOIN
--      ratings ON titles.title_id = ratings.title_id
-- INNER JOIN
--      crew ON titles.title_id = crew.title_id
-- INNER JOIN
--      people ON crew.person_id = people.person_id
-- WHERE people.name LIKE "%Cruise%" AND people.born = 1962
-- ORDER BY votes DESC
-- LIMIT 10;

-- Topics: Multi-table joins

-- Answer:
-- Oblivion|520383
-- Mission: Impossible|423228
-- Top Gun|408389
-- Magnolia|311030
-- Born on the Fourth of July|106667
-- Days of Thunder|88698
-- Lions for Lambs|50257
-- Without Limits|7127
-- Space Station 3D|1693
-- Nickelodeon Kids' Choice Awards 2012|212
