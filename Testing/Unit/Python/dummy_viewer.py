#! /usr/bin/env python3

import sys

out = ""
if len(sys.argv) > 1:
    out = " ".join(sys.argv[1:])

print(out)
