#Python code to find BER of BPSK
#Written by Vaibhav
#ECE 6710: Sprint 1
#Instead taking generating random input/output files, this program generates both Message, BPSK Tx Signal,
#..BPSK Rx Signal, dectection (based on BPSK threshold <0), Detected Signal and finally computes BER


#Program can be modified to take dynamic input files (i.e msg and detected) using 
#with open("c:\ECE6170\input_file.dat", "rb") as f:
#        msg = np.fromfile(f,dtype)
#with open("c:\ECE6170\ouput_file.dat", "rb") as f:
#        d = np.fromfile(f,dtype)

#for sake of simplicity N = 10, EbNo = 6, code works for higher values of N, and different EbNo



import numpy as np
#Message
N=10 # Number of Bits in the Message Signals
#Generates random message signal with [0,1] of length N, can be repalced with binary file input later
msg = np.random.randint(2, size=N) 


#Creating a BPSK Tx Signal
#to be replaced with BPSK modulutor 
EbNo = 6
sigma = np.sqrt(1/(2*1*EbNo))
s = 1 -2*msg #BPSK Signal 


#BPSK Rx Signal from AWGN Channel
#to be replaced with BPSK demodulator
r = s + sigma*np.random.randn(N) #BPSK Subjected to AWGN (recieved signal)

#Detection 
d = 1*(r<0)

#Bit Error Rate Caculator
Nerrs=0 #set Number of errors = 0 
for i in range(0,N-1):
    if msg[i] == d[i]:
       Nerrs = Nerrs+1

BER = (Nerrs)/(N)

print("Message        :", msg)
print("BPSK Signal    :", s)
print("Rx Signal      :", r)
print("Detected Signal:", d)
print("Number of Errors  :", Nerrs)
print("Bit Error Rate    :", BER)



