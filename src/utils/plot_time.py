#!/usr/bin/env python3
import sys
import matplotlib.pyplot as plt
import numpy as np
import json

def pwr(signal):
    pwr_linear = np.mean(np.abs(signal)**2)
    return 10*np.log10(pwr_linear)

def line2complex(line):
    vals = line.strip()[1:-1].split(',')
    if len(vals) == 2:
        return float(vals[0]) + 1j*float(vals[1])
    else:
        return None


def main():

    values = []

    while True:
        line = sys.stdin.readline()
        # print(line, end='')
        num = line2complex(line)
        if not (num is None):
            values.append(num)
        else:
            break
    print(len(values))
    plt.title("Real and Imaginary Signal Components")
    plt.plot(np.real(values))
    plt.plot(np.imag(values))

    plt.show()
    # print(f"Average Power = {pwr(np.array(values))}  dB")

if __name__=="__main__":
    main()
