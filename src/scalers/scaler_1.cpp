#include <iostream>
#include <complex>

using namespace std;

//used for testing AGC functionality
//creates a waveform with an increasing gain
int main(){

    complex<float> inc = 1;

    complex<float> sample;

    while(true){

        cin >> sample;

        if (cin.eof()) 
            break;

        cout << sample*inc << endl;

        inc += 0.01;


    }

}