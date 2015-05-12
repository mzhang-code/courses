import random
import sys

COURSE_NUM = 10

for l in sys.stdin:
    email, name, major = l.strip().split('|')
    cnt = random.randrange(0, COURSE_NUM + 1)
    courses = random.sample(range(COURSE_NUM), cnt) 
    for c in courses:
        print '|'.join(map(str, [email, c]))

