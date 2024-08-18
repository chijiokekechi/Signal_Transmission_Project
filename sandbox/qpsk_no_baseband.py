from pylab import *

def raise_cosine_fir_taps(n_syms=32, sps=16, beta=0.00):
    n = arange(-n_syms*sps//2, n_syms*sps//2)
    eps = 1e-12 # adding this to n to fix divide by zero errors
    return n, sinc(n/sps)*cos(beta*pi*(n + eps)/sps)/(1 - (2*beta*(n + eps)/sps)**2)

def main():
    M = 4  # only works for M = 4 right now.... 
    n_bits = 1000
    Es = 2
    snr_db = 13
    samples_per_symbol = 16
    beta = 0.1

    # time domain
    n, p = raise_cosine_fir_taps(sps=samples_per_symbol, beta=beta)

    # frequency domain
    n_fft = 4*len(p)
    f = fftshift(fftfreq(n_fft))
    P = fftshift(fft(p, n_fft))

    figure()
    plot(n/samples_per_symbol, p)
    xlabel(r'$t/T_s$')
    ylabel(r'$p(t)$')
    title(r'Raised-cosine pulse, $\beta = %g$, time-domain'%beta)
    grid()

    figure()
    plot(f*samples_per_symbol, abs(P))
    xlim(-1.1, 1.1)
    xlabel(r'$f/R_s$')
    ylabel(r'$P(f)$')
    title(r'Raised-cosine pulse, $\beta = %g$, frequency-domain'%beta)
    grid()


    # generating bit stream and calculating noise power level
    bits = randint(0, 2, n_bits)
    print('bits:', bits)
    bits_per_sym = int(round(log2(M)))
    num_syms = n_bits//bits_per_sym

    snr = 10**(snr_db/10)
    N0 = Es/snr # for two receive channels
    noise_std = sqrt(N0/2)

    # drawing constellation one symbol at a time
    figure()
    for n in range(0, n_bits, bits_per_sym):
        word = bits[n:n+bits_per_sym]

        if all(word == [0, 0]):
            sym = 1 + 1j
        elif all(word == [0, 1]):
            sym = -1 + 1j
        elif all(word == [1, 1]):
            sym = -1 - 1j
        elif all(word == [1, 0]):
            sym = 1 - 1j
        else:
            raise Exception

        # normalizing constellation point to correct energy per symbol
        sym *= sqrt(Es)/abs(sym)

        # adding noise with correct SNR
        sym += noise_std*randn() + 1j*noise_std*randn()

        plot(real(sym), imag(sym), 'b.')


    title('Constellation plot, QPSK, %g dB SNR, %d symbols'%(snr_db, n_bits/bits_per_sym))
    xlabel('In-phase channel (I)')
    ylabel('Quadrature channel (Q)')
    grid()
    axis('square')
    xlim(-1.5, 1.5)
    ylim(-1.5, 1.5)
    tight_layout()



    
    show()


if __name__ == '__main__':
    main()
