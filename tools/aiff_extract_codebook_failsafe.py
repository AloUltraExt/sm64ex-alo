#!/usr/bin/env python3
import sys
import os
import time
import subprocess

# example before: tools/aiff_extract_codebook sound/samples/sfx_custom_luigi/00.aiff >build/us_pc/sound/samples/sfx_custom_luigi/00.table


s_size = 0

# check arguments
if len(sys.argv) != 4:
    print(sys.argv[0] + ': was passed the incorrect number of arguments: ' + str(sys.argv), file=sys.stderr)
    exit(1)

# get arguments
a_cmd = sys.argv[1]
a_input = sys.argv[2]
a_output = sys.argv[3]

# validate input
if not os.path.isfile(a_input):
    print(sys.argv[0] + ': original input file does not exist "' + a_input + '"', file=sys.stderr)
else:
    # run original command
    s_cmd = [ a_cmd, a_input ]
    with open(a_output, 'w') as outfile:
        subprocess.call(s_cmd, stdout=outfile, shell=False)
        outfile.flush()
        os.fsync(outfile.fileno())

    # try to read the file length repeatedly
    s_itr = 0
    while s_size <= 0 and s_itr < 8:
        # sleep between iterations
        if s_itr > 0:
            time.sleep(0.1 + 0.05 * s_itr)
        s_itr += 1

        # check for existence
        if not os.path.isfile(a_output):
            continue

        # read file size
        with open(a_output, 'r') as outfile:
            s_text = outfile.read()
            s_size = len(s_text)

    # check final existence
    if not os.path.isfile(a_output):
        print(sys.argv[0] + ': original output file does not exist "' + a_output + '"', file=sys.stderr)

# check size
if s_size > 6:
    exit(0)
print(sys.argv[0] + ': original output file has a size of zero "' + a_output + '"', file=sys.stderr)

# only override custom
if 'custom' not in a_input:
    print(sys.argv[0] + ': original input file is not custom "' + a_input + '"', file=sys.stderr)
    exit(1)

# run override command
s_cmd = [ a_cmd, a_input ]
with open(a_output, 'w') as outfile:
    subprocess.call(s_cmd, stdout=outfile, shell=False)

# get size
if not os.path.isfile(a_output):
    print(sys.argv[0] + ': override output file does not exist "' + a_output + '"', file=sys.stderr)
else:
    with open(a_output, 'r') as outfile:
        s_text = outfile.read().strip()
        s_size = len(s_text)

# check size
if s_size <= 0:
    print(sys.argv[0] + ': override output file has a size of zero "' + a_output + '"', file=sys.stderr)
    exit(1)
