
//  Clark.cpp
//  ChannelModel
//
//  Created by Vaibhav Ravinutala on 4/12/22.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <complex>
#include <random>
#include <chrono>
#include <numeric>
using namespace std::complex_literals;


int main()
{
    int M=4;
    int fd=100;
   //int N=10000;
    float Ts=0.0001;
    int alpha=2;
    int beta=2;
    int theta=1;
    float x_n_re[5]= {1,2,3,4,5};
    float x_n_im[5]= {24,40,12,20,25};
    int len = sizeof(x_n_re);
    float h_n_re[5],h_n_im[5],mp_n_re[5],mp_n_im[5] = {0};
    float g_re[M];
    float g_im[M];
    float sum_g_re = 0;
    float sum_g_im = 0;
    float ct  = 2*M_PI*fd*Ts;
    
    //calculate h
    for(int n=0;n<=len-1;n++) {
        for(int m=0;m<=M-1;m++) {
            g_re[m] = (1/sqrt(M))*(cos(alpha+ (n)*ct*cos((((2*(m)-1)*M_PI+theta)/(4*(M))))));
            g_im[m] = (1/sqrt(M))*(sin(beta+  (n)*ct*cos((((2*(m)-1)*M_PI+theta)/(4*(M))))));
        }
        for(int i=0;i<=M-1;i++) {
            sum_g_re = 0;
            sum_g_re= g_re[i]+1;
            sum_g_im = 0;
            sum_g_im= g_im[i]+1;
        }
    h_n_re[n] = sum_g_re;
    h_n_im[n] = sum_g_im;
    }
    //calculate y
    for(int n=0;n<=len-1;n++) {
        mp_n_re[n] =  x_n_re[n]* h_n_re[n];
        mp_n_im[n] =  x_n_im[n]* h_n_im[n];
    }
    std:: cout<< "Input Signal"; std:: cout<< '\n';
    //print x
    std:: cout<< "x_n_re: ";
    for (auto i : x_n_re){ //C++11
    std:: cout <<i<< " ";
    }
    
    std:: cout<< '\n' <<"x_n_im: ";
    for (auto i : x_n_im){ //C++11
    std:: cout <<i<< " ";
    }
    std:: cout<< '\n';
    std:: cout<< '\n' << "Signal after multipath";
    //print y
    std:: cout<< '\n'<< "mp_n_re: ";
    for (auto i : mp_n_re){
    std:: cout <<i<< " ";
    }
    std:: cout<< '\n'<< "mp_n_im: ";
    for (auto i : mp_n_im){
    std:: cout <<i<< " ";
    } std:: cout<< '\n';
    std:: cout<< '\n';
    return 0;
}
