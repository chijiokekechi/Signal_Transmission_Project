from pylab import *
from scipy.signal import firwin, butter, lfilter, cheby2

def norm_angle(x):
    return angle(exp(1j*x))

def main():
    rx = loadtxt('out_filt.txt')
    sps = 16

    time_offset = 6
    time_k_p = 0.00
    time_k_i = 1.0
    time_integral = 0
    time_correction = 0

    pad = 200*sps
    N = len(rx)

    freq_offset = 0.000
    rx = roll(rx, time_offset + pad)*exp(2.j*pi*freq_offset*arange(N))
    rx[:time_offset + pad] = 0.


    sample_points = []
    errors = []
    for n in range(N):


        # symbol sync
        if (n%sps) == 0:
            truth = n + time_offset
            sym_num = truth//sps
            sample_point = int(round(n - time_correction))

            n_E = sample_point - sps//4
            n_L = sample_point - 3*sps//4
            if n_E >= N or n_L >= N or sample_point >= N:
                break

            sample_points.append(sample_point)


            if n_E > 0 and n_E < N:
                E = abs(rx[n_E])**2
            else:
                E = 0

            if n_L > 0 and n_E < N:
                L = abs(rx[n_L])**2
            else:
                L = 0

            time_discriminant = (E - L)/(E + L + 1e-12)
            time_integral += time_discriminant

            time_correction = time_k_p*time_discriminant + time_k_i*time_integral

            time_error = sample_point - truth
            errors.append(time_error)

            print('sym_num:', sym_num, 'truth:', truth, 'sample_point:', sample_point, 'time_error:', time_error, 'time_correction:', time_correction)

    xlims = (0, N - 1)

    figure()
    subplot(2,1,1)
    plot(rx.real)
    plot(sample_points, rx[sample_points].real, 'x')
    grid()
    xlim(*xlims)

    subplot(2,1,2)
    plot(sample_points, errors, '.')
    grid()
    xlim(*xlims)
    #ylim(-1.2, 1.2)
    ylabel('timing time_error')


    show()

if __name__ == '__main__':
    main()
