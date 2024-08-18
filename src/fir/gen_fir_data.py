#!/usr/bin/env python3
from pylab import *

def main():
    nsyms = 20
    sps = 8

    snr = 1e99
    noise_var = 1/snr

    u = zeros(nsyms*sps, dtype=complex64) # complex 64 has real & imag as 32 bit floats

    # generating signal
    for sym_num in range(nsyms):
        u[sym_num*sps:(sym_num + 1)*sps] = 2*randint(0, 2) - 1

    # adding noise
    u += sqrt(noise_var)*randn(*u.shape)      # real noise
    u += 1j*sqrt(noise_var)*randn(*u.shape)   # imag noise

    for sample in u:
        # print 7 points past decimal, field width of 10, fixed point
        print('%10.7f, %10.7f'%(sample.real, sample.imag))


if __name__ == '__main__':
    main()
