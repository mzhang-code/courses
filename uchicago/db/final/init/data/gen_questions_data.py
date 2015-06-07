import sys
import random

enrolls = [l.split('|') for l in sys.stdin]

sample = random.sample(enrolls, 200) 

T = [
     'MySQL Load Data Error', 
     'Assignment-related questions', 
     'Weak entities and relationships in MySQL', 
     'When is the Gradiance HW due tim', 
     'Access Denial when Reading Data']

C = [ 
     "I'm trying to give MySQL Workbench a go - it seems to have quite a few nice features to help with modeling and SQL scripting - but I'm having issues connecting to our MySQL server with the instructions available on Canvas. The application itself is running fine - just won't connect.", 
     "I'm having difficulty loading data to my tables from a file. MySQL repeatedly throws a 'file not found' error despite the fact that I am providing a valid directory for a .dat file. Even with the absolute path to the data file, it refuses to load.", 
     "Just a friendly reminder that if you have any question regarding your submitted assignments after receiving your grades, please post your questions here on Piazza (you can make it either public or private to Instructors).", 
     "Anh recommended that certain relationships & entity sets be considered weak entities in a revised ERD for my final project. Will this change the tables I create in MySQL? If so, how?", 
     "last two weeks it's been due at Midnight the night before class. I noticed the due date is 5:00 today.", 
     "When I attempt to read data, I get the following error message: ERROR 1045 (28000): Access denied for user 'cdward'@'%' (using password: YES)"]


for i, v in enumerate(sample):
    sid, cid = v
    idx = random.randrange(len(T)) 
    print '|'.join(map(str, [i, cid.strip(), sid.strip(), 'true', T[idx], C[idx]])) 

