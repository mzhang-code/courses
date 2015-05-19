
/* 1. show names of all students who selected course #8. 
   This query should return, 
   +-------------+----------------------+
   | name        | email                |
   +-------------+----------------------+
   | Ada         | ada00@uchicago.edu   |
   | Adeline     | adeline00@uchicago.e |
   | Adeline     | adeline03@uchicago.e |
   | Adrian      | adrian00@uchicago.ed |
   | Adrian      | adrian01@uchicago.ed |
   | Adrienne    | adrienne01@uchicago. |
   | Agustina    | agustina00@uchicago. |
   | Aja         | aja01@uchicago.edu   |
   | Alaine      | alaine00@uchicago.ed |
   | Alana       | alana00@uchicago.edu |
   | Alana       | alana01@uchicago.edu |
   | Albertine   | albertine00@uchicago |
   | Albina      | albina01@uchicago.ed |
   ...

   | Yuriko      | yuriko00@uchicago.ed |
   | Zoe         | zoe01@uchicago.edu   |
   +-------------+----------------------+
*/ 

SELECT S.name, S.email
FROM Student S JOIN Enroll E
ON S.email = E.student_email 
AND E.course_id = 8;

/* 2. show students who selected some courses and the number of courses they have. 
   This query should return, 
*/

SELECT S.name, COUNT(E.course_id) AS cnt
FROM Student S JOIN Enroll E
ON S.email = E.student_email 
GROUP BY S.email
ORDER BY cnt; 

/* 3. show student pairs who select the same course
*/

SELECT distinct E1.student_email, E2.student_email
FROM Enroll E1 JOIN Enroll E2
USING (course_id)
WHERE E1.student_email < E2.student_email; 

/* 4. show numner of students who select the same course with each student. 
*/

SELECT E1.student_email, COUNT(E2.student_email) AS student_cnt
FROM Enroll E1 JOIN Enroll E2
USING (course_id)
WHERE E1.student_email <> E2.student_email
GROUP BY E1.student_email; 


/* 5. show student pairs who select more than 3 same courses. 
   This query should return, 
   +----------------------+----------------------+------------+
   | student_email        | student_email        | common_cnt |
   +----------------------+----------------------+------------+
   ...

   | yasmin00@uchicago.ed | zoe01@uchicago.edu   |          4 |
   | yasmin01@uchicago.ed | yuriko00@uchicago.ed |          6 |
   | yasmin01@uchicago.ed | zoe00@uchicago.edu   |          4 |
   | yer00@uchicago.edu   | yuriko00@uchicago.ed |          7 |
   | yer00@uchicago.edu   | zoe01@uchicago.edu   |          4 |
   | yuriko00@uchicago.ed | zoe00@uchicago.edu   |          5 |
   | yuriko00@uchicago.ed | zoe01@uchicago.edu   |          5 |
   +----------------------+----------------------+------------+
   576356 rows in set (1 min 24.84 sec)
*/

SELECT E1.student_email, E2.student_email, COUNT(*) AS common_cnt
FROM Enroll E1 JOIN Enroll E2
USING (course_id)
WHERE E1.student_email < E2.student_email
GROUP BY E1.student_email, E2.student_email
HAVING common_cnt > 3; 

/* 6. show the count of questions that every student posted in every course, using natural join on course_id and student_email. 
*/ 

SELECT E.student_email, E.course_id, E.code, COUNT(*) AS question_cnt
FROM Enroll E NATURAL JOIN Question Q
GROUP BY E.course_id, E.student_email; 


/* 7. show students and the number of courses they have, including students who have no course.
*/

SELECT S.name, S.email, COUNT(E.course_id) AS course_cnt
FROM Student S LEFT OUTER JOIN Enroll E
ON S.email = E.student_email 
GROUP BY S.email; 

/* 8. show students who have no courses. 
   This query should return, 
*/

SELECT S.name, S.email
FROM Student S LEFT OUTER JOIN Enroll E
ON S.email = E.student_email 
GROUP BY S.email
HAVING COUNT(E.course_id) < 1; 

/* 9. show students who have selected all the courses. 
   This query should return, 
*/

SELECT S.name, S.email
FROM Student S LEFT OUTER JOIN Enroll E
ON S.email = E.student_email 
GROUP BY S.email
HAVING COUNT(E.course_id) = (SELECT COUNT(*) FROM Course); 

/* 10. show courses which has less than 1000 students enrolled. 
   This query should return, 
   +-----------+------------------------------+-------------+
   | code      | title                        | student_num |
   +-----------+------------------------------+-------------+
   | MPCS53013 | big data                     |         992 |
   | MPCS50409 | database                     |         971 |
   | MPCS50678 | object oriented architecture |        1012 |
   | MPCS50203 | hpc                          |        1014 |
   | MPCS50102 | avdanced programming         |        1019 |
   | MPCS50101 | immersion programming        |         989 |
   | MPCS51036 | java programming             |         991 |
   | MPCS51040 | c programming                |        1005 |
   | MPCS51200 | software engineering         |         978 |
   | MPCS52011 | computer system              |         983 |
   +-----------+------------------------------+-------------+
*/


SELECT C.code, C.title, COUNT(*) AS student_num
FROM Enroll E JOIN Course C
ON E.course_id = C.id 
GROUP BY C.id C.code C.title
HAVING student_num < 1000; 

