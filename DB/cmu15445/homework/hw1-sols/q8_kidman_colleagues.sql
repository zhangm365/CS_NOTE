-- List the all the different actors and actresses who have starred in a work
-- with Nicole Kidman (born in 1967).

-- Detail:
-- Print only the names of the actors and actresses in alphabetical
-- order. The answer should include Nicole Kidman herself. Each name should
-- only appear once in the output.

WITH kidman_titles AS (
     SELECT
          DISTINCT(crew.title_id)
     FROM
          people
     INNER JOIN
          crew ON crew.person_id == people.person_id AND people.name == "Nicole Kidman" AND people.born == 1967
),
kidman_colleagues AS (
     SELECT
          DISTINCT(crew.person_id) AS id
     FROM crew
     WHERE (crew.category == "actor" OR crew.category == "actress") AND crew.title_id in kidman_titles
)
SELECT
     name
FROM
     people
JOIN
     kidman_colleagues ON kidman_colleagues.id = people.person_id
ORDER BY name ASC;


-- Topics: More complicated joins, potential ctes

-- Answer:
-- Betty Gilpin
-- Casey Affleck
-- Colin Farrell
-- Crista Flanagan
-- Danny Huston
-- Dennis Miller
-- Donald Sutherland
-- Ed Mantell
-- Fionnula Flanagan
-- Flora Cross
-- Fredrik Skavlan
-- Gus Mercurio
-- Halle Berry
-- Harris Yulin
-- J.K. Simmons
-- Jackson Bond
-- James Corden
-- Jason Bateman
-- Javier Bardem
-- Jesper Christensen
-- John Lithgow
-- Julianne Moore
-- Kai Lewins
-- Kyle Mooney
-- Lisa Flanagan
-- Liz Burch
-- Mahershala Ali
-- Maria Tran
-- Mark Strong
-- Nicholas Eadie
-- Nicole Kidman
-- Paul Bettany
-- Pauline Chan
-- Robert Pattinson
-- Russell Crowe
-- Sam Neill
-- Shailene Woodley
-- Sherie Graham
-- Simon Baker
-- Stellan Skarsgård
-- Tom Cruise
-- Valerie Yu
-- Veronica Lang
-- Will Ferrell
