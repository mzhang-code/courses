LOAD DATA
    LOCAL INFILE "data/courses.dat"
    REPLACE INTO TABLE Course
    FIELDS TERMINATED BY '|'
    (id, code, title, description);

LOAD DATA
    LOCAL INFILE "data/students.dat"
    REPLACE INTO TABLE Student
    FIELDS TERMINATED BY '|'
    (email, name, major); 

LOAD DATA
    LOCAL INFILE "data/instructors.dat"
    REPLACE INTO TABLE Instructor
    FIELDS TERMINATED BY '|'
    (email, name, role);

LOAD DATA
    LOCAL INFILE "data/enroll.dat"
    REPLACE INTO TABLE Enroll
    FIELDS TERMINATED BY '|'
    (student_email, course_id);

LOAD DATA
    LOCAL INFILE "data/teach.dat"
    REPLACE INTO TABLE Teach
    FIELDS TERMINATED BY '|'
    (instructor_email, course_id);

LOAD DATA
    LOCAL INFILE "data/announcement.dat"
    REPLACE INTO TABLE Announcement
    FIELDS TERMINATED BY '|'
    (id, course_id, title, content);

LOAD DATA
    LOCAL INFILE "data/questions.dat"
    REPLACE INTO TABLE Question
    FIELDS TERMINATED BY '|'
    (id, course_id, creator, visibility, title, content);

LOAD DATA
    LOCAL INFILE "data/answers.dat"
    REPLACE INTO TABLE Answer
    FIELDS TERMINATED BY '|'
    (id, creator, content, reply_to);
