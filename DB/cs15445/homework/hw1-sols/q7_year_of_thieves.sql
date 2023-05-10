-- List the number of works that premiered in the same year that "Army of
-- Thieves" premiered.

-- Detail:
-- Print only the total number of works. The answer should include
-- "Army of Thieves" itself. For this question, determine distinct works by
-- their title_id, not their names.

SELECT
     COUNT(DISTINCT titles.title_id)
FROM
     titles
WHERE premiered IN (SELECT premiered from titles where primary_title='Army of Thieves');

-- Topics: Subqueries

-- Answer:
-- 63843
