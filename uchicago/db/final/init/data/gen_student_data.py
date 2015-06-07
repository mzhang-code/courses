import sys
import random
from collections import defaultdict

M = ['Computer Science', 'Math', 'EE', 'Stats', 'Econ']

D = defaultdict(int)

# for line in sys.stdin: 
#     name = line.replace('\xc2\xa0', '').strip()
#     print name

for line in sys.stdin:
    name = line.strip()
    print '|'.join([
        '%s@uchicago.edu' %(name.lower()), 
        name, 
        random.choice(M), 'STUDENT']) 

