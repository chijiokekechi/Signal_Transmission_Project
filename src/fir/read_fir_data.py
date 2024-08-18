#!/usr/bin/env python3
from pylab import *

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
        num = line2complex(line)
        if not (num is None):
            values.append(num)
        else:
            break

    values = array(values)
    max_mag = max(abs(values))

    figure()

    subplot(2,1,1)
    plot(values.real)
    xlim(0, len(values) - 1)
    ylim(-max_mag, max_mag)
    ylabel('real')
    grid()

    subplot(2,1,2)
    plot(values.imag)
    xlim(0, len(values) - 1)
    ylim(-max_mag, max_mag)
    ylabel('imag')
    grid()

    show()

if __name__ == '__main__':
    main()
