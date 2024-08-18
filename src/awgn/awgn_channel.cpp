#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <complex>
#include <queue>
#include <cmath>
using namespace std;

float pwr(const std::vector<std::complex<float>>& samples,
	  int num_samples){
	std::complex<float> result_linear = 0.0;	

    for (int n = 0; n < num_samples; n++)
		result_linear += samples[n]*std::conj(samples[n]);
    return result_linear.real()/num_samples;
}

void output_block(std::vector<std::complex<float>>& signal_samples,
            std::vector<std::complex<float>>& noise_samples,
            float noise_scale,
	        int num_samples){
    for (int n = 0; n < num_samples; n++)
        std::cout << signal_samples[n] + noise_scale*noise_samples[n] << std::endl;
}

int main(int argc, char* argv[]) {

    const complex<float> i(0.0,1.0);
    complex<float> sample;
    int sample_idx = 0; // Keep track of how many samples were read in
    int awgn_block = 500;
    bool awgn_mode_known_signal_power = true;
    float snr_db = 2;
    float signal_power_db = 0;

    float snr_linear = pow(10, snr_db/10); // Linear representation of the signal to noise ratio.
    vector<complex<float>> input_samples(awgn_block, 0.0); // initial array
    vector<complex<float>> noise_samples(awgn_block, 0.0); // Noise array 
    
    float signal_power_linear = pow(10, signal_power_db/10); // Signal power (variance)
    float noise_power_linear = signal_power_linear/snr_linear; // Noise power relative to signal (variance)
    float noise_power_linear_actual = 0; // Noise power from PRNG (variance) NOT USED
    float noise_scale = 1;

    // Read command line arg!
    if (argc==2) {
        snr_db = stof(argv[1]);
        snr_linear = pow(10, snr_db/10);
    } 

    // Number of samples to read before adding noise. This is important because this
    // model assumes that we do _not_ know the signal power a priori, but instead compute 
    // noise a posteriori.
    if (awgn_mode_known_signal_power) {
        signal_power_linear = pow(10, signal_power_db/10); // Signal power (variance)
        noise_power_linear = signal_power_linear/snr_linear; // Noise power relative to signal (variance)
        noise_power_linear_actual = 0; // Noise power from PRNG (variance) NOT USED
        noise_scale = 1;
    } else {
        signal_power_linear = 0; // Signal power (variance)
        noise_power_linear = 1; // Noise power relative to signal (variance)
        noise_power_linear_actual = 0; // Noise power from PRNG (variance)
        noise_scale = 0; // Computed scaler to multiply noise samples to achieve the desired noise power.        
    }

    // PRNG
    default_random_engine generator;
    normal_distribution<float> distribution(0.0, sqrt(noise_power_linear/2));


    // cerr << "AWGN Channel Configuration" << endl;
    // cerr << "\tTarget SNR : " << snr_db << "dB" << endl;
    // if (awgn_mode_known_signal_power) {
    //     cerr << "\tAssuming signal power = 0 dB" << endl;
    // } else {
    //     cerr << "\tAssuming unknown signal power!" << endl;
    //     cerr << "\tAWGN Signal Block Size : " << awgn_block << "samples" << endl;
    // }

    while (true) {
        // read value from stdin
        // cerr << int(sample_idx % awgn_block) << endl;
		cin >> sample;
        if (cin.eof()) break;
        // cerr << input_samples[0] << input_samples[1] << input_samples[2] << input_samples[3] << input_samples[4] << input_samples[5] << endl;
        // TODO: signal power = 0?
        // cerr << "A" << endl;
        if (!awgn_mode_known_signal_power) {
            input_samples[int(sample_idx % awgn_block)] = sample;
            if (sample_idx%awgn_block == 0 && sample_idx != 0) {
            
                signal_power_linear = pwr(input_samples, awgn_block);
                noise_power_linear = signal_power_linear/snr_linear;

                for (int n = 0; n <= awgn_block; n++) {
                    noise_samples[n] = (distribution(generator) + i*distribution(generator));
                }
                noise_power_linear_actual = pwr(noise_samples, awgn_block);

                noise_scale = sqrt(noise_power_linear/noise_power_linear_actual);

                output_block(input_samples, noise_samples, noise_scale, awgn_block);
            }
        } else {
            cout << sample + noise_scale*(distribution(generator) + i*distribution(generator)) << endl;
        }

        sample_idx ++;
    }
    // samples_read = sample_idx - 1;

    // signal_power_linear = pwr(input_samples, samples_read);
    // noise_power_linear = signal_power_linear/snr_linear;

    // compute_noise(noise_samples, noise_power_linear, samples_read);

    // cerr << "===== AWGN Channel =====" << endl;
    // cerr << "\tSNR dB       : " << snr_db << endl;
    // cerr << "\tComputed Signal Power : " << round(10*log10(signal_power_linear)*100)/100 << " dB"<< endl;
    // cerr << "\tComputed Noise Power  : " << round(10*log10(pwr(noise_samples, num_samples))*100)/100 << " dB" << endl;

    // return 0;
}

