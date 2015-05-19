
/*
mysql> call showSelectedCourses('jim00@uchicago.edu');
+-----------+-----------------------+
| code      | title                 |
+-----------+-----------------------+
| MPCS50102 | avdanced programming  |
| MPCS50101 | immersion programming |
| MPCS51036 | java programming      |
| MPCS51040 | c programming         |
| MPCS52011 | computer system       |
+-----------+-----------------------+
5 rows in set (0.00 sec)

*/ 

/*
mysql> call findUnregisteredStudents;
+----------+-----+
| name     | cnt |
+----------+-----+
| Antione  |   0 |
| Babette  |   0 |
| Felecia  |   0 |
| Glennie  |   0 |
| Joyce    |   0 |
| Kathline |   0 |
| Susanne  |   0 |
+----------+-----+
7 rows in set (0.04 sec)
*/ 

/*

Swap two courses. 

mysql> select * from Enroll where student_email = 'jim00@uchicago.edu'; 
+--------------------+-----------+
| student_email      | course_id |
+--------------------+-----------+
| jim00@uchicago.edu |         4 |
| jim00@uchicago.edu |         5 |
| jim00@uchicago.edu |         6 |
| jim00@uchicago.edu |         7 |
| jim00@uchicago.edu |         9 |
+--------------------+-----------+

mysql> call swapCourse('jim00@uchicago.edu', 2, 4); 

mysql> select * from Enroll where student_email = 'jim00@uchicago.edu'; 
+--------------------+-----------+
| student_email      | course_id |
+--------------------+-----------+
| jim00@uchicago.edu |         2 |
| jim00@uchicago.edu |         5 |
| jim00@uchicago.edu |         6 |
| jim00@uchicago.edu |         7 |
| jim00@uchicago.edu |         9 |
+--------------------+-----------+
*/ 
