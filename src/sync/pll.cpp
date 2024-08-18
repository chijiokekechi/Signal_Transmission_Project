/*Brandon Nieman PLL (Phase Locked Loop) in C++ for use in ECE6710 
Wireless Communication Systems with Dr. Cooke
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <complex.h>
#include <cmath>

using namespace std;
const int MAX_IN = 20000;


float largestFloat(float array[], int length){
    float max = array[0];

    for(int i=0; i<length; i++){
         if(array[i] > max){
               max = array[i];
         }
    }

    return max;
} 


int main(int argc, char *argv[])
{	
	const complex<double> j(0.0,1.0);

	FILE *filePtr;
	char *filename = argv[1];
	int N = 0;
	float Extractor = 0;
	complex<double> data[MAX_IN] = {0};
	
	filePtr = fopen(filename, "r");
	if(filePtr == NULL)
	{
		printf("ERROR opening file\n");
		exit(EXIT_FAILURE);
	}else{
		printf("Now Reading\n");
		while(fscanf(filePtr, "%f ", &Extractor) != EOF)
		{
			data[N] = Extractor;
			N++;
			if(N > MAX_IN)
			{
				printf("Error: The data block you loaded is too large.\n");
				exit(EXIT_FAILURE);	
			}
		}
	}
	fclose(filePtr);
	printf("Data Block Loaded, Size: %d\n", N);

    complex<double> freqOff = 0.0005;
    //float phaseOff = 0.00f;

	complex<double> phaseIntegral = 0.000;
	complex<double> freqCorrection = 0.000;

	complex<double> constellationSize = 2;

	//loop filter params - PID - using same as Dr. Cooke for now (pll.py)
	complex<double> phase_k_p = 0.0000;
	complex<double> phase_k_i = 0.0100;
	complex<double> phase_k_d = 0.0000;

	//remaking data with phase and freq changes, likely not necessary when getting real data
	
	for(int i = 0; i < N; i++)
	{
		data[i] = data[i] * exp(j*(double)2*M_PI*freqOff*(double)i);
	}


	complex<double> fixed[N] = {0};
	complex<double> vco[N] = {1}; // This doesn't fill the array with ones
	complex<double> vco_half[N] = {1}; // I kept these like this because they still need to be declared and the ones help me remember
	complex<double> stripped[N] = {0};
	complex<double> phase_error_last = 0;

	fill_n(vco, N, 1); //This does fill the array with ones
	fill_n(vco_half, N, 1);

	complex<double> multiplied = 0;
	complex<double> phaseError = 0;
	complex<double> phaseDeriv = 0;
	float abs_stripped[N] = {0};

	for(int n = 0; n < N; n++)
	{
		vco_half[n] = exp((double)2*j*M_PI*freqCorrection/constellationSize*(double)n);
		fixed[n] = data[n]*conj(vco_half[n]);
		multiplied = pow(data[n], constellationSize);
		stripped[n] = multiplied;

		//phase comparator
		vco[n] = exp((double)2*j*M_PI*freqCorrection*(double)n);
		phaseError = imag(stripped[n]*conj(vco[n]));

		//computing phase correction
		phaseIntegral += phaseError;
		phaseDeriv = phaseError - phase_error_last;
		freqCorrection = phase_k_p*phaseError + phase_k_i*phaseIntegral + phase_k_d*phaseDeriv;

		//updating buffer
		phase_error_last = phaseError;

		cout << "Freq Correction: " << real(freqCorrection);
		cout << " Phase Error: " << real(phaseError) << "\n";
		abs_stripped[n] = fabs(stripped[n]);

	}
	complex<double> max_stripped = largestFloat(abs_stripped,N);
	complex<double> strippedPlot[N]={0};
	for (int l = 0; l<N; l++)
	{
		strippedPlot[l] = stripped[l]/max_stripped;
	}

	//For PLOTTING in python
	//Stripped Data***********************************
	ofstream strippedFile ("stripped.txt");
	if (strippedFile.is_open())
	{
    for(int count = 0; count < N; count ++){
        strippedFile << real(strippedPlot[count]) << "," << imag(strippedPlot[count]) << "\n";
    }
    strippedFile.close();
	}
	else cout << "Unable to open file";

	//VCO data****************************************
	ofstream vcoFile ("vco.txt");
	if (vcoFile.is_open())
	{
    for(int count1 = 0; count1 < N; count1 ++){
        vcoFile << real(vco[count1]) << "," << imag(vco[count1]) << "\n";
    }
    vcoFile.close();
	}
	else cout << "Unable to open file";
  
	//data plot****************************************
	ofstream dataFile ("data.txt");
	if (dataFile.is_open())
	{
    for(int count2 = 0; count2 < N; count2 ++){
        dataFile << real(data[count2]) << "," << imag(data[count2]) << "\n";
    }
    dataFile.close();
	}
	else cout << "Unable to open file";	

	//Fixed Data***************************************

	ofstream fixedFile ("fixed.txt");
	if (fixedFile.is_open())
	{
    for(int count3 = 0; count3 < N; count3 ++){
        fixedFile << real(fixed[count3]) << "," << imag(fixed[count3]) << "\n";
    }
    fixedFile.close();
	}
	else cout << "Unable to open file";	

  return 0;

}


