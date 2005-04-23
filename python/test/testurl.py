from tst import *
from itertools import *
from time import clock

f = CallableFilter(lambda k,d,o: o)

print f.perform("test",0,"It works !");

t = TST()
# t = dict()

total_lines = 0
total_size = 0

SLICE = 100000

start = clock()
for line_number, line in enumerate(islice(open('url-list.txt','rb'),SLICE)):
    line = line.strip()
    t[line]=line_number
    total_size += len(line)
    if line_number%1000==0:
        print line_number, total_size, line
print 'Load : %f'%(clock()-start)
print 'Lines: %i Bytes: %i'%(line_number+1,total_size)

raw_input('Check memory')

start = clock()
for line_number, line in enumerate(islice(open('url-list.txt','rb'),SLICE)):
    line = line.strip()
    assert t[line]==line_number
print 'Read : %f'%(clock()-start)
