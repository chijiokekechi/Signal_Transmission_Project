#include <iostream>
#include <complex>
#include <vector>
#include <deque>

using namespace std;

std::deque<complex<float>> randomComp(int length){

    std::deque<complex<float>> randBuffer; 

    for (int i = 0 ; i < length ;i++)
    {
        float real = rand() %2;   
        float imag = rand() %2;    

        std::complex<float> mycomplex(real, imag); 

        randBuffer.push_front(mycomplex);
    }

    return randBuffer;
}

int main(){

    vector<complex<float>> syncTest= {{1,1}, {1,1}, {-1,-1}, {-1,-1}, {1,1}, {1,1}}; 

    std::deque<complex<float>> leadingRand = randomComp(20);

    std::deque<complex<float>> trailingRand = randomComp(20);

    for (int i = 0 ; i < 20 ; i ++){
        std::cout << leadingRand[i] << endl;
    }

    for (int i = 0 ; i < 6 ; i ++){
        std::cout << syncTest[i] << endl;
    }
    
    for (int i = 0 ; i < 20 ; i ++){
        std::cout << trailingRand[i] << endl;
    }

    
}

