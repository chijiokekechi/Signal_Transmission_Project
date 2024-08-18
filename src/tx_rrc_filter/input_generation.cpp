#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

using namespace std;
#define MAX_COEFF 100

int main()
{
    // Open a text file to write coefficients in them
    FILE *fp = fopen("input.txt", "w+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    //Define array to store input in
    complex<int> in[MAX_COEFF];

    //Initialize input array 
    for (int i = 0; i < MAX_COEFF; i++)
        in[i] = 0;

    //Input Dirac function 
    for (int i = 0; i < MAX_COEFF; i++)
    {
        if (i%2 == 0)
        {   
            in[i] = 1 + I * 0;
        }
        else 
        {
            in[i] = 0 + I * 0;
        }

        fprintf(fp,"%f %f\n", creal(in[i]), cimag(in[i]));
    }
    
}
