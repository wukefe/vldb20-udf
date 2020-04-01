
import sys

count = 0
isFunc = False

for line in sys.stdin:
    if line.startswith("function"):
        isFunc = True
        count = 1
    elif line.startswith("end"):
        isFunc = False
        count = count + 1
    elif isFunc:
        count = count + 1

print count

