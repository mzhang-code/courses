LOAD DATA
    LOCAL INFILE "data/courses.dat"
    REPLACE INTO TABLE Course
    FIELDS TERMINATED BY '|'
    (id, code, title, description);

LOAD DATA
    LOCAL INFILE "data/users.dat"
    REPLACE INTO TABLE User
    FIELDS TERMINATED BY '|'
    (email, name, dept, role); 

LOAD DATA
    LOCAL INFILE "data/enrolls.dat"
    REPLACE INTO TABLE Enroll
    FIELDS TERMINATED BY '|'
    (email, course_id);

LOAD DATA
    LOCAL INFILE "data/announcements.dat"
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
