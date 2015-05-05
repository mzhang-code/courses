
/* 1. show names of all students who selected course #8. 
   This query should return, 
   +--------+
   | name   |
   +--------+
   | Elis   |
   | Mengyu |
   | Tom    |
   +--------+
*/ 

SELECT S.name 
FROM Student S JOIN Enroll E
ON S.email = E.student_email 
AND E.course_id = 8;

/* 2. show students who selected courses as well as the number of courses they have. 
   This query should return, 
   +--------+--------------------+
   | name   | COUNT(E.course_id) |
   +--------+--------------------+
   | Elis   |                  3 |
   | Mengyu |                  7 |
   | Tom    |                  5 |
   +--------+--------------------+
*/

SELECT S.name, COUNT(E.course_id) 
FROM Student S JOIN Enroll E
ON S.email = E.student_email 
GROUP BY S.name; 


/* 3. show student pairs who select the same course
   This query should return, 
   +----------------------+----------------------+
   | student_email        | student_email        |
   +----------------------+----------------------+
   | mengyuzhang@uchicago | tm@uiuc.edu          |
   | elis@uchicago.edu    | mengyuzhang@uchicago |
   | elis@uchicago.edu    | tm@uiuc.edu          |
   +----------------------+----------------------+
*/

SELECT distinct E1.student_email, E2.student_email
FROM Enroll E1 JOIN Enroll E2
USING (course_id)
WHERE E1.student_email < E2.student_email; 

/* 4. show numner of students who select the same course with each student.
   This query should return, 
   +----------------------+-------------------------+
   | student_email        | COUNT(E2.student_email) |
   +----------------------+-------------------------+
   | elis@uchicago.edu    |                       4 |
   | mengyuzhang@uchicago |                       7 |
   | tm@uiuc.edu          |                       7 |
   +----------------------+-------------------------+
*/

SELECT E1.student_email, COUNT(E2.student_email)
FROM Enroll E1 JOIN Enroll E2
USING (course_id)
WHERE E1.student_email <> E2.student_email
GROUP BY E1.student_email; 


/* 5. show announcements that each student should receive, using natual join on attr (course_id).
   This query should return, 
   +----------------------+----------------------------------------------------------+
   | student_email        | title                                                    |
   +----------------------+----------------------------------------------------------+
   | mengyuzhang@uchicago | No Office Hours Today                                    |
   | tm@uiuc.edu          | No Office Hours Today                                    |
   | mengyuzhang@uchicago | Office Hours moved to Tuesday                            |
   | tm@uiuc.edu          | Office Hours moved to Tuesday                            |
   | elis@uchicago.edu    | HW3 Due Date Change; No Wednesday office hours this week |
   +----------------------+----------------------------------------------------------+
*/ 

SELECT E.student_email, A.title
FROM Enroll E NATURAL JOIN Announcement A
LIMIT 5;

/* 6. show number of announcements that each student should receive, using natual join on attr (course_id).
   This query should return, 
   +----------------------+----------------+
   | student_email        | COUNT(A.title) |
   +----------------------+----------------+
   | elis@uchicago.edu    |              4 |
   | mengyuzhang@uchicago |              8 |
   | tm@uiuc.edu          |              7 |
   +----------------------+----------------+
*/

SELECT E.student_email, COUNT(A.title)
FROM Enroll E NATURAL JOIN Announcement A
GROUP BY E.student_email; 


/* 7. show students and the number of courses they have, including students who have no course.
   This query should return, 
   +--------+--------------------+
   | name   | COUNT(E.course_id) |
   +--------+--------------------+
   | Alice  |                  0 |
   | Bob    |                  0 |
   | David  |                  0 |
   | Elis   |                  3 |
   | Jack   |                  0 |
   | Kobe   |                  0 |
   | Mengyu |                  7 |
   | Messi  |                  0 |
   | reg    |                  0 |
   | Tom    |                  5 |
   | Wang   |                  0 |
   +--------+--------------------+
*/

SELECT S.name, COUNT(E.course_id) 
FROM Student S LEFT OUTER JOIN Enroll E
ON S.email = E.student_email 
GROUP BY S.name; 

