
CREATE TABLE Course (
    id          int PRIMARY KEY, 
    code        varchar(10), 
    title       varchar(50),
    description text
);

CREATE TABLE Student (
    email       varchar(20) PRIMARY KEY, 
    name        varchar(20),
    major       varchar(20)
); 

CREATE TABLE Instructor (
    email       varchar(20) PRIMARY KEY, 
    name        varchar(20),
    role        varchar(20)
);

CREATE TABLE Enroll (
    student_email   varchar(20), 
    course_id       int, 
    PRIMARY KEY (student_email, course_id), 
    FOREIGN KEY (student_email) REFERENCES Student(email), 
    FOREIGN KEY (course_id) REFERENCES Course(id)
);

CREATE TABLE Teach (
    instructor_email    varchar(20), 
    course_id           int, 
    PRIMARY KEY (instructor_email, course_id), 
    FOREIGN KEY (instructor_email) REFERENCES Instructor(email), 
    FOREIGN KEY (course_id) REFERENCES Course(id)
);

CREATE TABLE Announcement (
    id          int PRIMARY KEY,
    course_id   int, 
    title       varchar(100), 
    content     text, 
    FOREIGN KEY (course_id) REFERENCES Course(id)
);

CREATE TABLE Question (
    id          int PRIMARY KEY, 
    course_id   int, 
    creator     varchar(20), 
    visibility  boolean, 
    title       varchar(100), 
    content     text, 
    FOREIGN KEY (creator) REFERENCES Student(email)
);

CREATE TABLE Answer ( 
    id          int PRIMARY KEY, 
    creator     varchar(20), 
    content     text, 
    reply_to    int, 
    FOREIGN KEY (reply_to) REFERENCES Question(id)
);
