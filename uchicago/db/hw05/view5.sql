
/* VIEW #1 */

CREATE VIEW EnrollResults AS
SELECT S.name, S.email, C.code, C.title
FROM Student S, Enroll E, Course C
WHERE S.email = E.student_email 
AND E.course_id = C.id; 

/* fetch all enroll records, 
   +--------+----------------------+-----------+------------------------------+
   | name   | email                | code      | title                        |
   +--------+----------------------+-----------+------------------------------+
   | Elis   | elis@uchicago.edu    | MPCS53013 | big data                     |
   | Mengyu | mengyuzhang@uchicago | MPCS50409 | database                     |
   | Mengyu | mengyuzhang@uchicago | MPCS50678 | object oriented architecture |
   | Tom    | tm@uiuc.edu          | MPCS50678 | object oriented architecture |
   | Mengyu | mengyuzhang@uchicago | MPCS50203 | hpc                          |
   | Tom    | tm@uiuc.edu          | MPCS50203 | hpc                          |
   | Mengyu | mengyuzhang@uchicago | MPCS51036 | java programming             |
   | Elis   | elis@uchicago.edu    | MPCS51040 | c programming                |
   | Mengyu | mengyuzhang@uchicago | MPCS51040 | c programming                |
   | Tom    | tm@uiuc.edu          | MPCS51040 | c programming                |
   | Elis   | elis@uchicago.edu    | MPCS51200 | software engineering         |
   | Mengyu | mengyuzhang@uchicago | MPCS51200 | software engineering         |
   | Tom    | tm@uiuc.edu          | MPCS51200 | software engineering         |
   | Mengyu | mengyuzhang@uchicago | MPCS52011 | computer system              |
   | Tom    | tm@uiuc.edu          | MPCS52011 | computer system              |
   +--------+----------------------+-----------+------------------------------+
*/

SELECT * FROM EnrollResults; 


/* query students who select "MPCS51040", 
   +--------+----------------------+
   | name   | email                |
   +--------+----------------------+
   | Elis   | elis@uchicago.edu    |
   | Mengyu | mengyuzhang@uchicago |
   | Tom    | tm@uiuc.edu          |
   +--------+----------------------+
*/

SELECT name, email 
FROM EnrollResults 
WHERE code = 'MPCS51040';


/* query student as well as the number of courses they choose.
   +--------+--------------+
   | name   | COUNT(title) |
   +--------+--------------+
   | Elis   |            3 |
   | Mengyu |            7 |
   | Tom    |            5 |
   +--------+--------------+
*/


SELECT name, COUNT(title)
FROM EnrollResults
GROUP BY name; 

/* VIEW #2 */

CREATE VIEW RegisterCount AS
SELECT S.name AS name, COUNT(E.course_id) AS cnt
FROM Student S LEFT OUTER JOIN Enroll E
ON S.email = E.student_email 
GROUP BY S.name; 

/* fetch all records,
   +--------+-----+
   | name   | cnt |
   +--------+-----+
   | Alice  |   0 |
   | Bob    |   0 |
   | David  |   0 |
   | Elis   |   3 |
   | Jack   |   0 |
   | Kobe   |   0 |
   | Mengyu |   7 |
   | Messi  |   0 |
   | reg    |   0 |
   | Tom    |   5 |
   | Wang   |   0 |
   +--------+-----+
*/ 

SELECT * FROM RegisterCount; 

/* query students who have no courses,
   +-------+
   | name  |
   +-------+
   | Alice |
   | Bob   |
   | David |
   | Jack  |
   | Kobe  |
   | Messi |
   | reg   |
   | Wang  |
   +-------+
*/

SELECT name 
FROM RegisterCount 
WHERE cnt = 0;

/* query students who have more than 4 courses,
   +--------+
   | name   |
   +--------+
   | Mengyu |
   | Tom    |
   +--------+
*/

SELECT name 
FROM RegisterCount 
WHERE cnt > 4;

