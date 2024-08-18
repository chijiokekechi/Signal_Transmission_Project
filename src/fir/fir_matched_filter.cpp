#include <iostream>
#include <iomanip>          // for setprecision
#include <vector>
#include <complex>
#include <queue>            // for deque

// this function computes the current output of the FIR filter
std::complex<float> fir_output(const std::vector<std::complex<float>>& taps,
                               const std::deque<std::complex<float>>& fir_sample_buffer){

    std::complex<float> output = 0.;

    for (int n = 0; n < taps.size(); n++)
        output += taps[n]*std::conj(fir_sample_buffer[n]);

    return output;
}

int main(int argc, char* argv[]) {
    
    using namespace std;
    int ntaps;

    if (argc == 2) {
        ntaps = stoi(argv[1]);  // stoi is "string to integer"
    }
    else {
        ntaps = 8;
    }

    // example moving average filter (rectangular pulse shape)
    vector<complex<float>> taps(ntaps, 1.f/ntaps); // initializing each value to 1/ntaps
    std::deque<complex<float>> fir_sample_buffer(taps.size(), 0.);

    /*
    for (int n = 0; n < taps.size(); n++)
        cout << taps[n] << endl;
    */

    complex<float> sample; 

    while (true) {
        // read value from stdin
        cin >> sample;

        if (cin.eof()) 
            break;

        // putting new sample in buffer
        fir_sample_buffer.pop_back();            // get rid of last value
        fir_sample_buffer.push_front(sample);    // push most recent value onto queue 

        // filter output and print to stdout
        cout << fir_output(taps, fir_sample_buffer) << endl;
    }


    return 0;
}
