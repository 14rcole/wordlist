import random, linecache

lineNum1 = random.randrange(1, 2482)
lineNum2 = random.randrange(1, 2482)

print linecache.getline("four-letter-words", lineNum1)
print linecache.getline("four-letter-words", lineNum2)
