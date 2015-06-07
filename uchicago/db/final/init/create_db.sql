
CREATE TABLE Course (
    id          int PRIMARY KEY, 
    code        varchar(10), 
    title       varchar(50),
    description text
);

CREATE TABLE User (
    email       varchar(20) PRIMARY KEY, 
    name        varchar(20),
    dept        varchar(20),
    role        varchar(10)
); 

CREATE TABLE Enroll (
    email   varchar(20), 
    course_id       int, 
    PRIMARY KEY (email, course_id), 
    FOREIGN KEY (email) REFERENCES User(email), 
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
    FOREIGN KEY (creator) REFERENCES User(email)
);

CREATE TABLE Answer ( 
    id          int PRIMARY KEY, 
    creator     varchar(20), 
    content     text, 
    reply_to    int, 
    FOREIGN KEY (reply_to) REFERENCES Question(id), 
    FOREIGN KEY (creator) REFERENCES User(email)
);
