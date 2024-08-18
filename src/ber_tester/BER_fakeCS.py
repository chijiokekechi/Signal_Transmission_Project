#!/usr/bin/python3
#Python code to find BER of BPSK
#Written by Vaibhav
#ECE 6710: Sprint 1
#Instead taking generating random input/output files, this program generates both Message, BPSK Tx Signal,
#..BPSK Rx Signal, dectection (based on BPSK threshold <0), Detected Signal and finally computes BER

#for sake of simplicity N = 10, EbNo = 0.1, code works for higher values of N, and different EbNo


import numpy as np
#Message
N=10 # Number of Bits in the Message Signals
#Generates random message signal with [0,1] of length N, can be repalced with binary file input later
msg = np.random.randint(2, size=N) 


#Creating a BPSK Tx Signal
#to be replaced with BPSK modulutor 
EbNo = 0.1
sigma = np.sqrt(1/(2*1*EbNo))
s = 1 -2*msg #BPSK Signal 

#BPSK Rx Signal from AWGN Channel
#to be replaced with BPSK demodulator
r = s + sigma*np.random.randn(N) #BPSK Subjected to AWGN (recieved signal)

#Detection 
d = 1*(r<0)

from numpy import save
save('input_file.npy', msg)
save('output_file.npy', d)
print("msg",msg)
print("d",d)

#EOF
