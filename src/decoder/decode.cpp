#include "decoder.hpp"
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

int main (int argc, char ** argv)
{
    string str;
    queue<complex<double>> * symbols = new queue<complex<double>>;  //decoder_t object takes care of destruction
    
    if (!cin.eof()) {
        getline(cin, str);
    }
    
    while (!cin.eof()) {
        char * cstr = const_cast<char*>(str.c_str());
        string delims = "(,)",
               real_str = strtok(cstr, delims.c_str());
        string imag_str = strtok(nullptr, delims.c_str());
        symbols->push(complex<double>(stod(real_str), stod(imag_str)));
        getline(cin, str);
    }
    
    decoder_t decoder (atoi(argv[1]), string("PSK"), symbols);
    
    while (!symbols->empty()) {
        cout << decoder.next().to_char();
    }
    
    cout << endl;
    return 0;
}
