from pylab import *

def norm_angle(x):
    return angle(exp(1j*x))

def main():
    rx = loadtxt('out_filt.txt')
    sps = 16


    freq_offset = 0.0005
    phase_k_p = 0.0000
    phase_k_i = 0.0100
    phase_k_d = 0.0000

    phase_integral = 0
    freq_correction = 0

    constellation_size = 2

    pad = 200*sps
    N = len(rx)

    rx = rx*exp(2.j*pi*freq_offset*arange(N))

    fixed = zeros(N, dtype=complex)
    vco = ones(N, dtype=complex)
    vco_half = ones(N, dtype=complex)
    stripped = zeros(N, dtype=complex)
    phase_error_last = 0.

    sample_points = []
    errors = []
    for n in range(N):

        vco_half[n] = exp(2.j*pi*freq_correction/constellation_size*n)
        fixed[n] = rx[n]*conj(vco_half[n])
        multiplied = rx[n]**constellation_size
        stripped[n] = multiplied

        # phase comparator
        vco[n] = exp(2.j*pi*freq_correction*n)
        phase_error = imag(stripped[n]*conj(vco[n]))

        # computing phase correction
        phase_integral += phase_error
        phase_derivative = phase_error - phase_error_last
        freq_correction = phase_k_p*phase_error + phase_k_i*phase_integral + \
                phase_k_d*phase_derivative

        # updating buffer
        phase_error_last = phase_error

        print('freq_correction:', freq_correction, 'phase_error:', phase_error)

    figure()
    plot(stripped/max(abs(stripped)))
    plot(vco)
    legend(('stripped', 'vco'))

    figure()
    subplot(2,1,1)
    plot(rx)
    subplot(2,1,2)
    plot(fixed)

    show()

if __name__ == '__main__':
    main()
