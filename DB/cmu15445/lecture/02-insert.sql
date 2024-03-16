
-- DDL
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


-- DML: INSERT
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


-- select : base

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

-- NESTED QUERIES
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