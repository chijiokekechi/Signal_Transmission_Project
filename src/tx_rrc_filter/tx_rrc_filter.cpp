#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <stdbool.h>

using namespace std;
//Definitions
#define ELEMENT_COUNT(X) (sizeof(X) / sizeof((X)[0]))
#define pi 3.14159265358979323846  //declare pi
#define MAX_COEFF 1000

//Main function
int main(int argc, char *argv[]) {
  
 int ntaps;
 float b;      //roll-off factor

 if (argc <= 1) 
  {
    ntaps = 8;
    b = 0.35;   
  }
  else {
    ntaps = atoi(argv[1]);  // stoi is "string to integer"
    b = atof(argv[2]);  // stoi is "string to integer"  
  }


  // Open a text file to write coefficients in them
  FILE *fp = fopen("coefficients.txt", "w+");
  if (fp == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }


  //Root raised cosine pulse filter parameters
  int Ts = 64; 
  int Rs = 1/Ts; 
  if ( !(ntaps % 2) )
  ntaps = ntaps +1;
  int ub = ( (ntaps - 1) / 2 ) + 1;  // upper bound of time range
  int lb= -(ntaps - 1) / 2;  // lower bound of time range

  
  //Initializing RRC filter
  float RRCfilter[ntaps];  //SRRC filter
  size_t i;
  for( i=0; i < ntaps ; i++)
    RRCfilter[i] = 0;
  i=0;

  //Computing coefficients of srrc filter
  float sum = 0;   //To calculate sum of srrc pulse to normalize filter gain 
  float count = 0.0;  //starting point of the srrc filter

  for(count= lb ; count < ub ; count++)
  {
    if (count == 0)
      RRCfilter[i] = (1 - b + (4 * b / pi) ); // count = 0 singulatiry
    else if ( count == round(1 / (4 * b)) || count == -round(1 / (4 * b)) )
      RRCfilter[i] =  b / (sqrt(2) ) * ((1 + 2 / pi) * sin(pi / (4 * b)) + (1 - 2 / pi) * cos(pi / (4 * b)));
    else 
      RRCfilter[i] = ( sin( (pi * count) * ( 1 - b )) + (4 * b * count) * cos( (pi * count) * (1 + b)) ) / ( (pi * count)  * (1 - pow((4 * b * count),2)) );
    
    sum = sum + RRCfilter[i];

    //Print the rrc coefficients into file
    fprintf(fp, "%f\n", RRCfilter[i]);
    i++;
  }

  fclose(fp); // Close file 

  //Delcarations of input and output variables
  float sample_real;
  float sample_im; 
  complex<float> signal;
  float result;
  float complex yn;

  //Declare thee delay line
  static complex<float> xv[MAX_COEFF]={0.0};


  //Supplying input to the filter
  while (true) 
  {
    //input from stdin
    if(!(scanf(" %f%f",&sample_real, &sample_im) != EOF))
      break;

    //Change representation of input signal
    signal = sample_real + I * sample_im;

    ///Initializing the delay line
		for (int l = ntaps-1; l > 0; l--)
		  xv[l] = xv[l-1];
		xv[0] = signal;

    //Filter Impulse Response
    
    for (int n = 0; n < ntaps; n++)
		{
		 	yn += RRCfilter[n] * xv[n];
		}
		result = yn;
    yn=0;

    //Print to stdout
    printf("%f\n",result);

  } 

  return 0;

}
