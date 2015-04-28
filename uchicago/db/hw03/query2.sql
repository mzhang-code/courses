
select code, title from Course; 

select * from Enroll 
    where student_email = "megyuzhang@uchicago.edu"; 

select * from Announcement 
    where course_id = 8; 

select * from Course
    where code = "MPCS%"; 

select creator, content from Answer 
    where reply_to = 8;

select title, content from Question 
    where creator = "mengyuzhang@uchicago.edu" AND 
          course_id = 8; 

