#!/usr/bin/python3

import numpy as np

#Reads input and output files directly from Terminal 
#Command format $ ./ber_testerv1.0.py input_file.npy outputfile.npy
import sys
input_file = sys.argv[1]
output_file = sys.argv[2]

msg = np.load(input_file)
d   = np.load(output_file)

#Bit Error Rate Caculator
Nerrs=0 #set Number of errors = 0 
if np.size(msg)==np.size(d):
   for i in range(0,np.size(msg)-1):
      if msg[i] != d[i]:
       Nerrs = Nerrs+1
else:
   print("Error: Length mismatch. BER can't be calculated")

BER = (Nerrs)/(np.size(msg)-1)

print("Bit Error Rate    :", BER)

#EOF
