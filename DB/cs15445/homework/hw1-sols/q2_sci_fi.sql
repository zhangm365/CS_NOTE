-- Find the 10 Sci-Fi works with the longest runtimes.

-- Detail:
-- Print the title of the work, the premiere date, and the runtime.
-- The column listing the runtime should be suffixed with the string " (mins)",
-- for example, if the runtime_mins value is 12, you should output 12 (mins).
-- Note a work is Sci-Fi even if it is categorized in multiple genres,
-- as long as Sci-Fi is one of the genres.
--
-- Your first row should look like this:
-- Cicak-Man 2: Planet Hitam|2008|999 (mins)

SELECT
	primary_title, premiered, CAST(runtime_minutes AS VARCHAR) || " (mins)"
FROM
	titles
WHERE genres LIKE '%Sci-Fi%'
ORDER BY runtime_minutes DESC
LIMIT 10;

-- Topics: WHERE, ORDER BY, CAST, CONCAT

-- Answer:
-- Cicak-Man 2: Planet Hitam|2008|999 (mins)
-- Project Hail Mary|2021|970 (mins)
-- Wholy|2018|660 (mins)
-- Tales from the Void|2016|600 (mins)
-- Blade Runner: Czy androidy marza o elektrycznych owcach? (Audioplay)|2012|403 (mins)
-- Cold Lazarus|1996|300 (mins)
-- Phantom Gear|2021|300 (mins)
-- The Halt|2019|279 (mins)
-- V: The Final Battle|1984|272 (mins)
-- Atom Man vs. Superman|1950|252 (mins)
