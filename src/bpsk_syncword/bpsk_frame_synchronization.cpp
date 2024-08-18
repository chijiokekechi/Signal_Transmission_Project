#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <complex>
#include <queue>
#include <cmath>
using namespace std;

// this function computes the current output of the FIR filter
std::complex<float> fir_output(const std::vector<std::complex<float>>& taps,
                               const std::deque<std::complex<float>>& fir_sample_buffer){

    std::complex<float> output = 0.;

    for (int n = 0; n < taps.size(); n++)
        output += taps[n]*fir_sample_buffer[n];

    return output;
}


int main(int argc, char* argv[]) {

    complex<float> sample;
    int samples_per_symbol = 8;
    int offset = 0;
    int syncLength = 48;
    bool found = false;
    float threshold = 30;
    int count = 0;
    float mf_result = 0;
    float max_val = 0;
    int max_idx = 0;
    // Big endian because we are being sent data little endian.
    complex<float> syncword[syncLength] = {-1, 1, -1, 1, -1, 1, -1, 1, \
                                           -1, 1, -1, 1, -1, 1, -1, 1, \
                                           -1, 1, 1, 1, 1, 1, -1, 1, \
                                           -1, 1, 1, 1, 1, 1, -1, 1, \
                                           -1, 1, -1, 1, -1, 1, -1, 1, \
                                           -1, 1, -1, 1, -1, 1, -1, 1};
    vector<complex<float>> taps(syncLength*samples_per_symbol, 0.0);

    for (int i =0; i < syncLength; i++) {
        taps[(i+1)*samples_per_symbol] = syncword[syncLength - i - 1];
    }

    std::deque<complex<float>> fir_sample_buffer(syncLength*samples_per_symbol*2, 0.);
    std::deque<float> match_filter_out(syncLength*samples_per_symbol*2, 0.);

    while (true) {
        // read value from stdin
		
        cin >> sample;
        if (cin.eof()) break;

        // putting new sample in buffer
        fir_sample_buffer.pop_back();            // get rid of last value
        fir_sample_buffer.push_front(sample);    // push most recent value onto queue

        // cout << fir_output(taps, fir_sample_buffer) << endl;
        // filter output and print to stdout
        
        mf_result = real(fir_output(taps, fir_sample_buffer));
        match_filter_out.pop_back();
        match_filter_out.push_front(mf_result);

        // Check fir buffer if there is a peak past our threshold.
        if (!found) {
            max_idx = 0;
            max_val = 0;
            for (int i = 0; i < count; i++){
                if (match_filter_out[i] > max_val) {
                    max_val = match_filter_out[i];
                    max_idx = i;
                }
            }
            if (max_val > threshold && \
                    max_idx > 24*samples_per_symbol) { // Buffer length
                found=true;
                offset = max_idx + samples_per_symbol*syncLength + 1;
                for (int i=0; i < offset; i++){
                    cout << fir_sample_buffer[offset - i - 1] << endl;
                }
            } 
        } else {
            cout << sample << endl;
        }    
        // Note we need an end of frame as well to indicate we need to look for the next incomming
        //   Frame

        
        count ++;
    }
}

