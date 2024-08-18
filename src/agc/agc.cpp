#include <iostream>
#include <complex>
#include <queue>

using namespace std;

//this function takes in an array containing the current sample and previous sample from cin and passes them through the AGC filter.
//the filter will adjust the amplitude of the current sample based on a weighted sum of the energy of the current sample and previous sample.
//the variable alpha is what should be adjusted to change the weight of each term in the sum.
//the AGC function attempts to maintain a constant signal energy level 
void calcAGC(const deque<complex<float>>& sampleBuffer, complex<float> alpha){

    //compute the energy of both samples in the buffer
    float previousSignalEnergy = abs(sampleBuffer[1])*abs(sampleBuffer[1]);
    float currentSignalEnergy = abs(sampleBuffer[0])*abs(sampleBuffer[0]);

    //if the energies are both non-zero, activate the AGC filter. If either signal energy is zero than the filter is innactive
    if( previousSignalEnergy > 0 && currentSignalEnergy > 0){

        complex<float> currentGain = alpha*(sqrt(1.f/currentSignalEnergy)) + (1.f - alpha)*(sqrt(1.f/previousSignalEnergy));

        complex<float> currentOutput = sampleBuffer[0]*currentGain;
        cout << currentOutput << endl;

    }else{
        cout << sampleBuffer[0] << endl;
    }
}

int main(){

    complex<float> sample; 

    complex<float> alpha=0.1; 

    deque<complex<float>> sampleBuffer(2, 0.);
    

    while (true){

        // read value from stdin
        cin >> sample;

        if (cin.eof()) 
            break;

        //cycle the incoming data through the 2 sample buffer
        sampleBuffer.pop_back();
        sampleBuffer.push_front(sample);
        //adjust the amplitude with the AGC filter
        calcAGC(sampleBuffer, alpha);
 
    }
    
   
}
