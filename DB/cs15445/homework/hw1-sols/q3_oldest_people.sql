-- Determine the oldest people in the dataset who were born in or after 1900.
-- You should assume that a person without a known death year is still alive.

-- Detail:
-- Print the name and age of each person. People should be
-- ordered by a compound value of their age and secondly their name. Return
-- the first 20 results.
--
-- Your output should have the format:
-- NAME|AGE

SELECT name,
	CASE
		WHEN died IS NOT NULL
		THEN died - born
		ELSE 2022 - born
	END AS age
FROM
	people
WHERE born >= 1900
ORDER BY age DESC, name ASC
LIMIT 20;

-- Topics: Compound attributes, CASE

-- Answer:
-- C. Dickerman Williams|122
-- Charles Sherrin|122
-- Clint Denn|122
-- Eugênia Brasão|122
-- George Kuma|122
-- Hasso Price|122
-- Jaime Contreras|122
-- John Arthur Stockton|122
-- Kaoru Wakaba|122
-- Kichimatsu Nakamura|122
-- Léonide Azar|122
-- Manuel Díaz|122
-- Miklós Beck|122
-- Nikolay Solovyev|122
-- Olga Belajeff|122
-- Tatsuo Tomonari|122
-- Abdolhossein Sepenta|121
-- Annie Hémery|121
-- Bronislava Livia|121
-- Clemence Groves|121
