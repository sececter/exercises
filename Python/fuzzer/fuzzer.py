#!/usr/bin/python

# 5-line fuzzer below is from Charlie Miller's
# "Babysitting an Army of Monkeys":
# Part 1 - http://www.youtube.com/watch?v=Xnwodi2CBws
# Part 2 - http://www.youtube.com/watch?v=lK5fgCvS2N

# List of files to use as initial seed
file_list=[
    "Uc8Gr.jpg",
    "20150702_160430.jpg",
    "20150702_160444.jpg"
    ]

# List of applications to test
apps = [
    "/usr/bin/eog"
    ]

fuzz_output = "fuzz.jpg"


FuzzFactor = 250
num_tests = 10

########### end configuration ##########

import math
import random
import string
import subprocess
import time

for i in range(num_tests):
    file_choice = random.choice(file_list)
    app = random.choice(apps)

    buf = bytearray(open(file_choice, 'rb').read())

    # start Charlie Miller code
    numwrites=random.randrange(math.ceil((float(len(buf)) / FuzzFactor)))+1

    for j in range(numwrites):
        rbyte = random.randrange(256)
        rn = random.randrange(len(buf))
        buf[rn] = "%c"%(rbyte)
    #end Charlie Miller code

    open(fuzz_output, 'wb').write(buf)

    process = subprocess.Popen([app, fuzz_output])

    time.sleep(1)
    crashed = process.poll()
    if not crashed:
        process.terminate()
