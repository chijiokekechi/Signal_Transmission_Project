#include <iostream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <functional>
#include <bitset>
#include <random>
#include <chrono>

using namespace std;

#define PI 3.14
#define datalength 10 // number of generated input bits
float fc = 0.01;
float Es = 2;
int Ts = 64;
#define points 10 //number of gnerated samples ber bit to draw modulated signal
#define tmin 0
#define tmax (4*M_PI)
float outData[datalength][points];
float t;
float tin=0;
float t_m;




float *BPSK_mod(float *input, int size) //BPSK Modulation function
{
    for (int i = 0; i < size; i++) // loop over input bits
    {
        if (input[i] == 1){
         for (int k=1; k<points;k++){ // loop over time
         t=tin + k*(tmax-tmin)/(points-1);  // to keep track time "since it is reseted each loop" (total time period for all bits)
         t_m= tmin + k*(tmax-tmin)/(points-1); // time period  
        outData[i][k]= sqrt(Es) *cos(2*PI*fc*Ts*t_m); //Modulated signal if INPUT=1
        //cout << t << endl;
         }  
         tin=t;    // store the timme to be updated/incremented based on the last value 
        }
        else if (input[i] == 0){
         for (int k=1; k<points;k++){
             t=tin + k*(tmax-tmin)/(points-1);
             t_m= tmin + k*(tmax-tmin)/(points-1);
        outData[i][k]= -sqrt(Es) *cos(2*PI*fc*Ts*t_m); //Modulated signal if INPUT=0
        //cout << t << endl;
         }
         tin=t;
    
        }
    }
    return 0;
}

int main()
{
    float inData[datalength];
    
   float *C;
    int *D;
    float *output;
    float *input;
   
    
    for (int i = 0; i < datalength; i++)
    {
        inData[i]=rand()%2; 
        C = BPSK_mod(inData, datalength); //call modulation function
       
         std :: cout << inData[i]<< "--> " ; //print input data
         for (int k = 0; k < points; k++)
         {
            
            std :: cout << " " << outData[i][k]; //print modulated output data (samples for all bits)
         }
         

        cout << endl;   
    }



    return 0;
}

/*int main()
{
    int t=1;
    float fc=0.01;
    int Ts= 64;
    int Amp=1;
    float pi=3.14;
    cout << cos(2*pi*fc*t) <<endl;
    
    return 0;
}*/