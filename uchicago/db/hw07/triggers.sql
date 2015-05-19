
DELIMITER |

CREATE TRIGGER CourseDelTrigger
BEFORE DELETE on Course
FOR EACH ROW 
BEGIN 
    DELETE FROM Enroll WHERE course_id = OLD.id; 
    DELETE FROM Teach WHERE course_id = OLD.id; 
    DELETE FROM Announcement WHERE course_id = OLD.id; 
    DELETE FROM Question WHERE course_id = OLD.id; 
END; |

CREATE TRIGGER QuestionDelTrigger
BEFORE DELETE on Question
FOR EACH ROW 
BEGIN 
    DELETE FROM Answer WHERE reply_to = OLD.id; 
END; |

CREATE TRIGGER StudentDelTrigger
BEFORE DELETE on Student
FOR EACH ROW 
BEGIN 
    DELETE FROM Enroll WHERE student_email = OLD.email;
    DELETE FROM Quesiton WHERE creator = OLD.email;
END; |

DELIMITER ;

