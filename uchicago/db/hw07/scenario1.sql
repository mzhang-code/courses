
/* 
When CourseDelTrigger added, course deletion will trigger deletions on other correlated tables. For exmaple, when course #1 is deleted, all corresponding records in table Enroll are also deleted. 

mysql> delete from Course where id = 1;

mysql> select * from Enroll where course_id = 1;
Empty set (0.00 sec)
*/ 

DROP from Course where id = 1;
SELECT * from Enroll where course_id = 1;

/* Similarly, StudentDelTrigger maintains the validity when a student is deleted. 
*/ 

