#include <iostream>
#include <complex>

using namespace std;


//used for testing AGC functionality
//creates a waveform that stays constant for a while before an increasing gain is applied
int main(){

    int inc = 1;

    complex<float> inc2 = 1;

    complex<float> sample;

    while(true){

        cin >> sample;

        if (cin.eof()) 
            break;


        if (inc < 100){
            cout << sample << endl;
        }

    
        else {
            cout << sample*inc2 << endl;
            inc2+=0.11;
        }

        inc++;

    }

}