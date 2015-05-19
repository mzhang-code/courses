
/* In One Query */ 
/* may look like 
  +--------------+------------+
  | table_name   | table_size |
  +--------------+------------+
  | Announcement |         10 |
  | Answer       |          4 |
  | Course       |         10 |
  | Enroll       |      13041 |
  | Instructor   |          5 |
  | Question     |       1013 |
  | Student      |       1800 |
  | Teach        |          5 |
  +--------------+------------+
*/ 

SELECT TABLE_NAME AS 'table_name', sum(TABLE_ROWS) AS 'table_size' 
FROM INFORMATION_SCHEMA.TABLES 
WHERE TABLE_SCHEMA = 'mengyuzhangDB'
GROUP BY TABLE_NAME;


