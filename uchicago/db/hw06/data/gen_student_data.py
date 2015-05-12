import sys
import random
from collections import defaultdict

M = ['Computer Science', 'Math', 'EE', 'Stats', 'Econ']

D = defaultdict(int)

for line in sys.stdin: 
    name = line.replace('\xc2\xa0', '').strip()
    print name

# for name, cnt in D.items(): 
#     for i in range(cnt): 
#         print '|'.join([
#             '%s%02d@uchicago.edu' %(name.lower(), i), 
#             name, 
#             random.choice(M)]) 
# 
