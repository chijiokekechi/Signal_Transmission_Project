#include <iostream>         // piping input and outputs easily
#include <iomanip>          // for setprecision
#include <vector>           //to define vectors for our input, output and impulse response signal streams
#include <complex>          // Since we are dealing with comples numbers
#include <queue>            // for deque
#include <math.h>           // function for mathematical operations

//We define global variables
#define pi 3.141592653589793238463 //Standard pi definition for our use

// this function computes the current output of the FIR filter
std::complex<float> rrc_output(const std::vector<std::complex<float>>& ht,
                               const std::deque<std::complex<float>>& rrc_sample_buffer){

    std::complex<float> yt = 0.;

    //This loop would give us our final filtered output, which is the function of the 
    for (int n = 0; n < ht.size(); n++)
        yt += ht[n]*rrc_sample_buffer[n]; 

    return yt;
}

int main(int argc, char* argv[]) {
    
    using namespace std; //With this command, we do not have to include std before using any of the functions or properties of the std namespace
    int sps; //We define our "samples per symbol" variable as an integer
    float beta; //The roll-off or decay factor, usually denoted by beta
    int Ts = 64; // The sample period
    int Rs = 1/Ts; // This is the sample frequency or rate, which is the multiplicative inverse of the sample frequency
    int t;
//    if (!(sps%2)){
//        sps += 1;
//    }


    if (argc == 3) { //This enables us to iput command line arguments for Samples per symbol and roll-off factor
        sps = stoi(argv[1]);  // stoi is "string to integer". We are converting here because our sps variable was defined as an integer variable.
        beta = stof(argv[2]); // stof is "string to floating-point". We are converting because the beta function was defined as a floating-point variable.
        // This means that suppose we pass./rrc 8 0.3, rrc is argv[0], 8 is argv[1] and 0.3 is argv[2]
    }
    else {
        //If no command line arguments are specified for sps and beta, these are their default values:
        sps = 8; 
        beta = 0.3;
    }

    // example moving average filter (rectangular pulse shape)
    vector<complex<float>> ht(sps, 0); // specifying the range of our filter impulse response vector and initializing with zeros
    std::deque<complex<float>> rrc_sample_buffer(ht.size(), 0.); //The sample buffer size is the same as the impulse response vector
    // for (int i = 0; i< ht.size(); i++){

    //This entire loop gives impulse response for each instance of time for the specified range.
//    for (int i = (-sps/2); i< ((sps/2)+1); i++){
    for (int i = 1; i< ht.size()+1; i++){
        if (t == 0){
            ht[i] = Rs*(1+(beta*((4/pi)-1)));
        }
        else if ( t == (Ts/(4*beta)) || t == -(Ts/(4*beta))){
            ht[i] = (beta/Ts*sqrt(2))*((1+(2/pi))*sin(pi/(4*beta))+(1-(2/pi))*cos(pi/(4*beta)));
        }
        else{
            ht[i] = (Rs*(sin(pi*t*Rs*(1-beta))+(4*beta*t*Rs*cos(pi*t*Rs*(1-beta)))))/(pi*t*Rs*(1-pow((4*beta*t*Rs),2)));
        }
//        return ht;
    }

    /*
    for (int n = 0; n < taps.size(); n++)
        cout << taps[n] << endl;
    */

    complex<float> sample; 

    while (true) {
        // read the input sample value from stdin
        cin >> sample;

        if (cin.eof()) 
            break;

        // putting new sample in buffer
        rrc_sample_buffer.pop_back();            // get rid of last value
        rrc_sample_buffer.push_front(sample);    // push most recent value onto queue 

        // obtain the filter output and print to stdout
        cout << rrc_output(ht, rrc_sample_buffer) << endl;
    }


    return 0;
}
