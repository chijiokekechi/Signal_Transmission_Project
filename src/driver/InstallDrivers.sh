#!/bin/bash
## Installation of required software drives for Ettus devices


## Update Repos
sudo apt-get update


## Define the update function
function install_pkg {
	sudo apt-get -y install "$*"
}


## Prereq Installs
install_pkg g++
install_pkg make
install_pkg cmake
install_pkg git
install_pkg swig
install_pkg libpython3-dev
install_pkg python3-numpy


## Soapy installs
install_pkg soapysdr-tools
install_pkg libsoapysdr-dev
install_pkg python3-soapysdr


## Device Drivers and Support
install_pkg libuhd-dev
install_pkg libuhd3.15.0
install_pkg uhd-host
install_pkg uhd-soapysdr


## C++ Runtime Build
git clone https://github.com/pothosware/SoapySDR.git
cd SoapySDR
mkdir build
cd build
cmake ..
make -j4
sudo make install


## Finish Installation
sudo ldconfig #needed on debian systems


## Check installation
SoapySDRUtil --info
