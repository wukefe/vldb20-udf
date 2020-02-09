"""
Usage:
    cat sf1/perf_thread_12.txt | grep -A 1 "tuple" | python cut2.py
"""

import sys
import time
import fileinput

def procLine(line):
    run_time = line.split(':')[-1].split(' ')[0]
    return float(run_time)

def printRuns(runs):
    run_avg = sum(runs)/len(runs)
    print 'Average time (ms): %g | ' % run_avg ,
    for x in runs:
        print '%g' % x ,
    print ''

def main():
    if len(sys.argv) != 1:
        print "Usage: python cut.py <std_input>"
        sys.exit(1)
    runs = []
    lineno = 0
    nums = 15
    for line in fileinput.input():
    	line = line.strip('| \r\n')
        if lineno % 3 == 1:
            runs.append(procLine(line))
            if len(runs) == nums:
                printRuns(runs)
                runs = []
        lineno = lineno + 1
    if len(runs) == nums:
        printRuns(runs)
    elif len(runs) != 0:
        print 'Error: remaining runs %d but %d expected' % (len(runs),nums)
    pass

if __name__ == '__main__':
    #start = time.time()
    main()
    #sys.stderr.write('Elapsed time: %g ms\n' % (1000*(time.time() - start)))

## sql:0.000 opt:0.354 run:0.451 ms
## sql:0.288 opt:2.796 run:2094.822 ms


