
-- 1. DDL -----------------------------------
CREATE TABLE student (
    sid INT PRIMARY KEY,
    name VARCHAR(16),
    login VARCHAR(32) UNIQUE,
    age SMALLINT,
    gpa FLOAT
);

CREATE TABLE course (
    cid VARCHAR(32) PRIMARY KEY,
    name VARCHAR(32) NOT NULL
);

CREATE TABLE enrolled (
    sid INT REFERENCES student (sid),
    cid VARCHAR(32) REFERENCES course (cid),
    grade CHAR(1)
);
--------------------------------------------

-- 2. DML: INSERT --------------------------
insert into student values 
    (53666, 'RZA', 'rza@cs', 44, 4.0),
    (53688, 'Bieber', 'jbieber@cs', 27, 3.9),
    (53655, 'Tupac', 'shakur@cs', 25, 3.5);

insert into course values 
    ('15-445', 'Database Systems'),
    ('15-721', 'Advanced Database Systems'),
    ('15-826', 'Data Mining'),
    ('15-799', 'Special Topics in Databases');

insert into enrolled values 
    (53666, '15-445', 'C'),
    (53688, '15-721', 'A'),
    (53688, '15-826', 'B'),
    (53655, '15-445', 'B'),
    (53666, '15-721', 'C');
--------------------------------------------

-- 3. select : base

-- pgsql: ERROR:  column "e.cid" must appear in the GROUP BY clause or be used in an aggregate function 
-- SELECT AVG(s.gpa), e.cid FROM enrolled AS e JOIN student AS s ON e.sid = s.sid;

SELECT * 
FROM enrolled AS e, student AS s
WHERE e.sid = s.sid;

-- the same as above
SELECT * 
FROM enrolled AS e join student AS s on e.sid = s.sid;


SELECT AVG(s.gpa), e.cid 
FROM enrolled AS e, student AS s
WHERE e.sid = s.sid
GROUP BY e.cid;

-- pgsql: ERROR:  column "avg_gpa" does not exist
-- SELECT AVG(s.gpa) AS avg_gpa, e.cid
-- FROM enrolled AS e, student AS s
-- WHERE e.sid = s.sid
-- GROUP BY e.cid
-- HAVING avg_gpa > 3.9;

SELECT AVG(s.gpa) AS avg_gpa, e.cid
FROM enrolled AS e, student AS s
WHERE e.sid = s.sid
GROUP BY e.cid
HAVING AVG(s.gpa) > 3.9;


-- 4. string function ---------------------
SELECT SUBSTRING(name,1,5) AS abbrv_name
FROM student WHERE sid = 53688;


--- 5. output redirection
--- store the query results in another table.
-- SQL-92
SELECT DISTINCT cid INTO CourseIds
FROM enrolled;

-- Postgres, the temporary table is in pg_temp_3 schema, while the default schema is public if it isn't temporary table.
SELECT DISTINCT cid
INTO TEMPORARY CourseIds
FROM enrolled;

-- mysql
CREATE TABLE CourseIds (
    SELECT DISTINCT cid FROM enrolled);

-- order by
SELECT sid, grade FROM enrolled
WHERE cid = '15-721'
ORDER BY 2;

-- fetch first # rows
SELECT sid, name FROM student
WHERE login LIKE '%@cs'
FETCH FIRST 10 ROWS ONLY;

-- fetch first # rows with ties(包括并列行)
SELECT sid, name FROM student
WHERE login LIKE '%@cs'
ORDER BY gpa
OFFSET 10 ROWS
FETCH FIRST 10 ROWS WITH TIES;

-- 6. NESTED QUERIES
-- Find the names of students who are enrolled in 15-445
select name from student where sid in (select sid from enrolled where cid = '15-445');

-- Find student record with the highest id that is enrolled in at least one course.
select sid, name from student where sid in (select max(sid) from enrolled);

-- method 2
SELECT sid, name FROM student
    WHERE sid IN (
        SELECT sid FROM enrolled
        ORDER BY sid DESC LIMIT 1
    )
;

SELECT name FROM student
WHERE sid in (
    SELECT sid FROM enrolled
    WHERE cid = '15-445'
);

-- same as the above
SELECT name FROM student
WHERE sid = any (
    SELECT sid FROM enrolled
    WHERE cid = '15-445'
);

-- ERROR:  column "s.name" must appear in the GROUP BY clause or be used in an aggregate function
SELECT MAX(e.sid), s.name
FROM enrolled AS e, student AS s
WHERE e.sid = s.sid;

SELECT sid, name FROM student
WHERE sid IN (
    SELECT MAX(sid) FROM enrolled
);


SELECT sid, name FROM student
WHERE sid IN (
SELECT sid FROM enrolled
ORDER BY sid DESC FETCH FIRST 1 ROW ONLY
);


-- method 3
SELECT student.sid, name
    FROM student
    JOIN (SELECT MAX(sid) AS sid
    FROM enrolled) AS max_e
        ON student.sid = max_e.sid
;

-- Find all courses that have no students enrolled in it.
select course.cid from course where course.cid not in (
    select cid from enrolled
        where course.cid = enrolled.cid
);

-- method 2, not exists
select course.cid from course where not exists (
    select cid from enrolled
        where course.cid = enrolled.cid
);


-- 7. window function: row_number, 在当前行引入一个行号
-- over: 切分规则
SELECT *, ROW_NUMBER() OVER () AS row_num
FROM enrolled;

-- RANK: 当前行的排名
SELECT *, RANK() OVER () AS rank
FROM enrolled;

-- 使用 partition by 语义，对每个 cid 分别计算 row_number
SELECT *, ROW_NUMBER() OVER (partition by cid) AS row_num
FROM enrolled
order by cid;

SELECT *, ROW_NUMBER() OVER (order by cid) AS row_num
FROM enrolled
order by cid;

-- 查找：以 cid 分组，对每个 cid 的学生成绩进行排序，找到第二高的学生成绩
SELECT * FROM (
    SELECT *, RANK() OVER (PARTITION BY cid
    ORDER BY grade ASC) AS rank
    FROM enrolled) AS ranking
WHERE ranking.rank = 2;



--- 8. common table expression
WITH cteName AS (
SELECT 1
)
SELECT * FROM cteName;


WITH cteSource (maxId) AS (
SELECT MAX(sid) FROM enrolled
)
SELECT name FROM student, cteSource
WHERE student.sid = cteSource.maxId;


--- 9. lateral join
SELECT * FROM
(SELECT 1 AS x) AS t1,
LATERAL (SELECT t1.x+1 AS y) AS t2;

SELECT * FROM course AS c,
LATERAL (SELECT COUNT(*) AS cnt FROM enrolled  -- Compute the # of enrolled students
WHERE enrolled.cid = c.cid) AS t1,
LATERAL (SELECT AVG(gpa) AS avg FROM student AS s  -- Compute the average gpa of enrolled students
JOIN enrolled AS e ON s.sid = e.sid
WHERE e.cid = c.cid) AS t2;
