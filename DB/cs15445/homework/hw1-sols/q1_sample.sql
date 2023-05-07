-- The purpose of this query is to make sure that the formatting of your output matches exactly the
-- formatting of our auto-grading script.

-- Detail:
-- List all unique languages of dubs ordered alphabetically.

SELECT
	DISTINCT(language)
FROM
	akas
ORDER BY language
LIMIT 10;

-- Topics: Sanity check environment and grader

-- Answer:
--
-- af
-- ar
-- az
-- be
-- bg
-- bn
-- bs
-- ca
-- cmn
