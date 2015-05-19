
DELIMITER |
CREATE PROCEDURE showSelectedCourses(
    IN student_email varchar(20)) 
BEGIN 
    SELECT C.code, C.title 
    FROM Enroll E, Course C
    WHERE E.course_id = C.id AND E.student_email = student_email; 
END |

CREATE PROCEDURE findUnregisteredStudents()
BEGIN
    SELECT S.name, COUNT(E.course_id) AS cnt
    FROM Student S LEFT OUTER JOIN Enroll E
    ON S.email = E.student_email 
    GROUP BY S.name
    HAVING cnt = 0; 
END | 

CREATE PROCEDURE swapCourse(
    IN student varchar(20), 
    IN course_in int, 
    IN course_out int)
BEGIN 
    DELETE FROM Enroll where student_email = student AND course_id = course_out;
    INSERT IGNORE Enroll VALUES(student, course_in); 
END | 

