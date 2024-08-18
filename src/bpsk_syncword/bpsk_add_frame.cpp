#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <complex>
#include <queue>
#include <cmath>
using namespace std;


int main(int argc, char* argv[]) {

    complex<float> sample;
    std::string line;
    std::string syncword = "UUAAUU";
    bool sent = false;

    while (true) {
        // read value from stdin
        // cerr << int(sample_idx % awgn_block) << endl;
		cin >> line;
        if (cin.eof()) {
            break;
        }

        if (sent) {
            cout << line << endl;
        } else {
            cout << syncword << line << endl;
            sent = true;
        }
    }
}

