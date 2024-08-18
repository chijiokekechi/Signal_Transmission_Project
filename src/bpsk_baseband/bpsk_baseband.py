#!/usr/bin/env python3
from pylab import *
import scipy.stats

# this is some text

def rect(t, Ts):
    midval = 1.
    radius = 1.
    h = heaviside(t/Ts + radius/2, midval) - heaviside(t/Ts - radius/2, midval)

    # normalization factor to make it unit energy
    h *= sqrt(2/Ts)

    return h

def rrc(t, Ts, beta):
    # root raised cosine

    h = zeros(t.shape)

    i1 = t == 0
    if beta != 0:
        i2 = abs(t) == Ts/(4*beta)
    else:
        i2 = False*i1
    i3 = ~(i1 | i2)

    # formula from wikipedia
    h[i1] = 1/Ts*(1 + beta*(4/pi - 1))
    if any(i2):
        h[i2] = beta/(Ts*sqrt(2))*((1 + 2/pi)*sin(pi/(4*beta)) + (1 - 2/pi)*cos(pi/(4*beta)))
    h[i3] = 1/Ts*(sin(pi*t[i3]/Ts*(1 - beta)) + 4*beta*t[i3]/Ts*cos(pi*t[i3]/Ts*(1 + beta)))/\
            (pi*t[i3]/Ts*(1 - (4*beta*t[i3]/Ts)**2))

    # normalization factor to make it unit energy
    h *= sqrt(2*Ts)

    return h

def rc(t, Ts, beta):
    # raised cosine

    p = zeros(t.shape)

    if beta != 0:
        i1 = abs(t) == Ts/(2*beta)
    else:
        i1 = zeros(t.shape, dtype=bool)
    i2 = ~i1

    if any(i1):
        p[i1] = pi/4*sinc(1/(2*beta))
    p[i2] = sinc(t[i2]/Ts)*(cos(beta*pi*t[i2]/Ts)/(1 - (2*beta*t[i2]/Ts)**2))

    # normalization factor to make it unit energy
    p *= sqrt(2/Ts)/sqrt(1 - beta/4)

    return p

def main():
                                                                                                                                  
    # inputs
    n_sym = 20
    Ts = 64                                 # symbol period
    Es = 1                                  # energy per symbol
    N0 = 0.5                                # one-sided noise PSD
    beta = 0.3
    fc = 0.10                               # normalized frequency
    pulse_shape = 'Rect'

    # misc
    Q = scipy.stats.norm.sf                 # gaussian Q function
    Rs = 1/Ts                               # symbol rate
    B = (1 + beta)*Rs                       # bandwidth
    snr = Es/(N0*B)
    snr_db = 10*log10(snr)
    print('snr_db:', snr_db)
    Eb = Es
    EbN0_db = 10*log10(Eb/N0)
    print('EbN0_db:', EbN0_db)
    bits = randint(0, 2, n_sym)

    # pulse shaping filter
    filt_syms = 16
    filt_len = Ts*filt_syms + 1
    chop = filt_len//2
    t_filt = arange(-chop, chop + 1) - Ts/2 # shifting over a bit
    if pulse_shape == 'Rect':
        g = rect(t_filt, Ts)
    elif pulse_shape == 'RC':
        g = rc(t_filt, Ts, beta)
    elif pulse_shape == 'RRC':
        g = rrc(t_filt, Ts, beta)
    else:
        raise Exception('invalid pulse type')
    mf = conj(g[::-1])                      # matched filter

    figure()
    plot(t_filt/Ts, g)
    xlabel(r'$t/T_s$')
    ylabel(r'$g(t)$')
    if pulse_shape == 'Rect':
        title('%s pulse shape'%pulse_shape)
    elif beta > 0:
        title(r'%s pulse shape, $\beta = %g$'%(pulse_shape, beta))
    else:
        title(r'Sinc pulse shape')
    grid()


    # symbols modulated to deltas
    t = arange(-n_sym//2*Ts, n_sym//2*Ts)
    z = zeros(t.shape)
    syms = sqrt(Es)*(2*bits - 1)
    for m in t[::Ts]:
        sym_num = m//Ts
        z[m] = syms[sym_num]

    # pulse shaping
    u = convolve(z, g, 'full')[chop:-chop]

    # RF signal
    s = real(u*exp(2j*pi*fc*t))

    # RX baseband signal
    v = u/2 # factor of 1/2 is from equivalent LP channel

    # receive matched filtering. 
    v_filt = convolve(v, mf, 'full')[chop:-chop]
    
    # adding noise
    v_noise = v_filt + sqrt(N0/2)*randn(*v_filt.shape)

    # detecting bits
    detected_bits = (v_noise[::Ts] > 0).astype(int)
    BER_emp = mean(detected_bits != bits)
    print('BER_emp:', BER_emp)
    BER_theory = Q(sqrt(2*Eb/N0))
    print('BER_theory:', BER_theory)

    if n_sym <= 1000:
        figure(figsize=(8, 9))

        subplot(5,1,1)
        plot(t/Ts, z)
        #plot(t[::Ts]/Ts, u[::Ts], 'x')
        xlim(min(t/Ts), max(t/Ts))
        #xticks(arange(-n_sym//2, n_sym//2))
        ylabel(r'$z(t)$')
        title('BPSK w/ %s pulse shape; SNR = %.1f dB; $E_b/N_0$ = %.1f dB'%(pulse_shape, snr_db, EbN0_db))
        grid()

        subplot(5,1,2)
        plot(t/Ts, u)
        #plot(t[::Ts]/Ts, u[::Ts], 'x')
        xlim(min(t/Ts), max(t/Ts))
        #xticks(arange(-n_sym//2, n_sym//2))
        ylabel(r'$u(t) = z(t)*g(t)$')
        grid()

        subplot(5,1,3)
        plot(t/Ts, s)
        #plot(t[::Ts]/Ts, u[::Ts], 'x')
        xlim(min(t/Ts), max(t/Ts))
        #xticks(arange(-n_sym//2, n_sym//2))
        ylabel(r'$s(t)$')
        grid()

        subplot(5,1,4)
        plot(t/Ts, v_filt)
        plot(t[::Ts]/Ts, v_filt[::Ts], 'x')
        xlim(min(t/Ts), max(t/Ts))
        #xticks(arange(-n_sym//2, n_sym//2))
        yticks([-sqrt(Es), 0, sqrt(Es)])
        ylabel(r'$v(t) * g^*(-t)$')
        grid()

        subplot(5,1,5)
        plot(t/Ts, v_noise)
        plot(t[::Ts]/Ts, v_noise[::Ts], 'x')
        xlim(min(t/Ts), max(t/Ts))
        #xticks(arange(-n_sym//2, n_sym//2))
        xlabel(r'$t/T_s$')
        ylabel(r'$(v(t) + $ noise $) * g^*(-t)$')
        grid()


        tight_layout()
        show()

    else:
        print('number of symbols too large to plot (> 1000)')


if __name__ == '__main__':
    main()
