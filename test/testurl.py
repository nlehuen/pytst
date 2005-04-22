from tst import *
from itertools import *

t = TST()

total_size = 0

for line_number, line in enumerate(islice(open('url-list.txt','rb'),700000)):
    line = line.strip()
    t[line]=1
    total_size += len(line)
    if line_number%1000==0:
        print line_number, total_size, line
    
print "OK"


