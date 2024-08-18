#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<float> distribution(0, 1); // zero mean, unit variance
    distribution(generator); // "warming up" the RNG

    // example generating a bunch
    for (int n = 0; n < 10; n++) {
        cout << distribution(generator);
        cout << ",";
        cout << distribution(generator) << endl;
    }

    return 0;
}
