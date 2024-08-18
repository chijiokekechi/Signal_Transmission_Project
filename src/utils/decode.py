#!/usr/bin/env python3
import sys
import matplotlib.pyplot as plt
import numpy as np
import json


def line2int(line):
    vals = line.strip().split('0x')
    if len(vals) == 2:
        return int(vals[1], 16)
    else:
        return None


def main():

    values = []

    while True:
        line = sys.stdin.readline()
        num = line2int(line)

        if not (num is None):
            values.append(num)
        else:
            break

        print(f"{chr(int(bin(num)[2:].zfill(8)[::-1], 2))}", end='')


if __name__=="__main__":
    main()
    print()