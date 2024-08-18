#!/usr/bin/env python3
from pylab import *
import math as m
import numpy as np
import sys,getopt

def line2complex(line):
    vals = line.strip()[1:-1].split(',')
    if len(vals) == 2:
        return float(vals[0]) + 1j*float(vals[1])
    else:
        return None

def main(self):
    values = []
    
    if len(sys.argv) == 2:
        name = sys.argv[1]
    else:
        name = "Constellation Plot"

    while True:
        line = sys.stdin.readline()

        # Pass the line forward to allow for intermediate pipeline debugging.
        print(line, end='')
        num = line2complex(line)
        if not (num is None):
            values.append(num)
        else:
            break

    values = np.array(values)
    # max_mag = max(abs(values))
    
    EMM = 2
    # em = np.arange(0,EMM)
    em = 0
    I_Part = np.real(values)
    Q_Part = np.imag(values)
    # for part in values:
    #for em in range(0,EMM):
    #    I_Part = np.real(values) * np.cos((np.pi * 2 * em) / EMM )
    #    Q_Part = np.imag(values) * np.sin((np.pi * 2 * em) / EMM )
        # I_Part = np.real(part) * m.cos((m.pi *(2*em) + 1) / EMM )
        # Q_Part = np.imag(part) * m.sin((m.pi *(2*em) + 1) / EMM )
        # I_Part = values.real * m.cos((m.pi *(2*em) + 1) / EMM )
        # Q_Part = values.imag * m.sin((m.pi *(2*em) + 1) / EMM )
            

    figure()

    subplot(1,1,1)
    plot((I_Part), Q_Part, '.')
    # ylim(-max_mag, max_mag)
    # xlim(-max_mag, max_mag)
    ylabel('Q (Imaginary Part/ Quadrature)')
    xlabel('I (Real Part/ Inphase)')
    title(name)
    grid()

    # subplot(2,1,2)
    # plot(values.imag)
    # ylim(-max_mag, max_mag)
    # ylabel('imag')
    # grid()

    show()

if __name__ == '__main__':
    main(sys.argv)
