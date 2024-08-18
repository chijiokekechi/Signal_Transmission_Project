#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <stdlib.h>  

using namespace std;
using namespace std::complex_literals;

string real_string;
string imag_string;
float real_sample = 0;
float imag_sample = 0;

float snr_dB = 0;
float snr_linear = 0;
float noise_power_linear = 0;
float signal_power_linear = 1;

double real_temp = 0;
double imag_temp = 0;
float random_num = -100;

int main(int argc, char* argv[]) {
	if(argc == 2)
	{
		snr_dB = stof(argv[1]);
	    snr_linear = std::pow(10, snr_dB/10);
		noise_power_linear = signal_power_linear/snr_linear;
    }
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
	normal_distribution<float> distribution(0, sqrt(noise_power_linear/2)); // zero mean, user variance
    distribution(generator); // "warming up" the RNG
	
	//Read in clean samples
	getline(cin,real_string,',');
	while (!cin.eof()) 
	{
		// read value from stdin
		getline(cin,imag_string);

		real_sample = stof(real_string);
		imag_sample = stof(imag_string);
		
		random_num = distribution(generator);
		real_temp = real_sample+random_num;
		random_num = distribution(generator);
		imag_temp = imag_sample+random_num;
        //const std::complex<float> AWGN_signal(real_temp, imag_temp);
		
		cout << real_temp << "," << imag_temp << endl;
		
		getline(cin,real_string,',');
	}
    return 0;
}
