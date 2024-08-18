#!/bin/bash
# This script will build for any changes and run BasicStream.exe

g++ BasicStream.cpp -o BasicStream -lSoapySDR

./BasicStream
