#include <iostream>
#include <complex>
#include <bitset>
#include <cstdint>
#include <string>
#include <cstdlib>
#include <queue>
#include <iomanip>
#include <exception>
#include "byte.hpp" //byte_t
#include <map>
#include <cstring>
#include "gray_code.hpp"    //gray_code_t, constellation_t, encode
#include "error_msgs.hpp"   //error msgs, BPSK, QPSK

using namespace std;
//TODO: Consider turning DEBUG away from being a global variable
bool DEBUG = false; //used to turn on debug mode (TODO: an std::future might be handy for this somehow)

const double PI = acos(-1);
const complex<double> ZERO (0, 0);

byte_t read_byte (string&);
void create_symbol_queue (queue<byte_t>&, const int, const char**);
void psk (queue<byte_t>&, const uint8_t, const int16_t);

int main (int argc, char ** argv)
{
    uint8_t samples_per_symbol;
    string mod_technique;
    cout << fixed;
    //read in command line args and handle user input error for samples_per_symbol and mod_technique
    switch (argc) {
        case 4: DEBUG = !strcmp(argv[3], "--debug");
        
        case 3: //NOTE: The program will still act like the user entered 1 even when they enter 0,
                //      but I thought it would just be confusing if that went unchecked. Also, the
                //      casting to void is necessary for this to work.
                atoi(argv[1]) < 1 ? error::invalid_num_samples_msg() :
                                    static_cast<void>(samples_per_symbol = atoi(argv[1]));
                mod_technique = argv[2];
                break;
        
        case 2: if (!strcmp(argv[1], "--help")) {
                    error::accepted_mod_types_msg();
                    error::how_to();
                    cout << endl;
                }
                else error::mod_type_missing_msg();
                return 0;   //NOTE: only run if help option is used
        
        default: error::invalid_num_arguments();
    }
    
    queue<byte_t> symbols;
    create_symbol_queue(symbols, argc, const_cast<const char**>(argv));
    
    //TODO: See if there's a better way to check for this (regex maybe?).
    //check type of modulation and run relevant function for modulation type
    if (mod_technique == BPSK) {
        psk(symbols, samples_per_symbol, 2);
    }
    else if (mod_technique == QPSK) {
        psk(symbols, samples_per_symbol, 4);
    }
    else if (mod_technique == PSK8) {
        psk(symbols, samples_per_symbol, 8);
    }
    else if (mod_technique == PSK16) {
        psk(symbols, samples_per_symbol, 16);
    }
    else if (mod_technique == PSK256) {
        psk(symbols, samples_per_symbol, 256);
    }
    //TODO: Other modulation types are to be added here
    else {
        error::invalid_mod_type_msg();
    }
    
    return 0;
}

/**
 * Name: read_byte
 * Purpose: Returns the next byte (char) from an input string and
 *          reduces the input string's length by 1 by effectively
 *          "popping" the front character from the string.
 */
byte_t read_byte (string & str)
{
    uint8_t ch = str.front();
    str = str.substr(1);    // this is effectively a pop function as used here
    return byte_t(ch);
}

/**
 * Name: create_symbol_queue
 * Purpose: Reads piped input symbols into a queue for BPSK modulation. The queue is passed by
 *          reference, hence this is a void function.
 */
void create_symbol_queue (queue<byte_t> & symbols, const int ARGC, const char ** ARGV)
{
    string str;
    
    if (!cin.eof()) {
        getline(cin, str);
    }
    
    while (!cin.eof()) {
        while (!str.empty()) {
            symbols.push(read_byte(str));
        }
        
        getline(cin, str);
    }
    
    if (DEBUG) {    //prints every item in the queue while preserving them
        cout << "Printing out symbol queue..." << endl;
        
        for (uint8_t i = 0; i < symbols.size(); i++) {
            cout << symbols.front().to_int() << " -> "  << symbols.front() << endl;
            symbols.push(symbols.front());
            symbols.pop();
        }
    }
}

void psk (queue<byte_t> & symbols, const uint8_t SAMPLES_PER_SYMBOL, const int16_t M)
{
    gray_code_t gc;
    constellation_t constellation;
    encode(M, "PSK", gc, constellation);
    const uint8_t K = static_cast<uint8_t>(floor(log2(M)));
    
    cout << fixed;
    if (DEBUG) {
        for (uint16_t i = 0; i < M; i++) {
            cout << "gc[" << i + 0 << "]: " << gc.at(i) + 0 << endl;    //+0 is just a cleaner way to
        }                                                               //cast here (more readable)
        for (uint16_t i = 0; i < M; i++) {
            cout << "S" << i + 1 << ": " << constellation.at(i) << endl;
        }
    }
    
    //NOTE: Reverse the constellation in the case of BPSK (this just for display and to condense the
    //      code below)
    if (M == 2) {
        constellation.push_back(constellation.at(0));
        constellation.pop_front();
    }
    
    while (!symbols.empty()) {  //TODO: what to do when symbols is empty but leftover is not?
        if (DEBUG) {
            cout << symbols.front().to_int() << " -> " << symbols.front() << endl;
        }
        
        if (K % 2 != 0) {   //NOTE: This is currently only meant for 8-PSK
            static uint8_t bits_left = 0;
            static byte_t leftover;
            for (uint8_t i = (bits_left == 0 ? 0 : K - bits_left); i < 8; i += K) {
            //for (uint8_t i = bits_left; i < 8; i += K) {
                uint8_t count = 0;              //TODO: This loop messes up whenever i == 7
                //cout << "i: " << i+0 << endl;
                //if (8 - i < K) {
                //if (i + K > 8) {  //NOTE: This is the problem child here
                //cout << "Symbol: " << symbols.front().to_int() << endl;
                //cout << boolalpha << (symbols.front().to_int() >= 4) << endl;
                /*if (symbols.front().to_int() < 4) {
                    bits_left = 8 - i;
                    //if (8 - i == 2) {   //i = 6
                        leftover = symbols.front();
                        //cout << "bits_left: " << bits_left+0 << endl;
                    //}
                    //else if (8 - i == 1) {  //i = 7
                    //    leftover = symbols.front() >> ???;
                    //}
                }*/
                
                //else {
                if (symbols.front().to_int() >= 4) {
                    //cout << "bits_left: " << bits_left << endl;
                    for (uint8_t j = 0; j < bits_left; j++) {
                        if ((leftover & 1).to_int()) {
                            count += pow(2, j);
                        }
                        leftover >>= 1;
                    }
                    for (uint8_t j = bits_left; j < K; j++) {
                        if ((symbols.front() & 1).to_int()) {
                            count += pow(2, j);
                        }
                        symbols.front() >>= 1;
                        //leftover >>= 1;
                    }
                    //cout << "count: " << count+0 << endl;
                    bits_left = 0;
                    cout << constellation.at(gc.at(count)) << endl;
                    for (int8_t i = 0; i < SAMPLES_PER_SYMBOL - 1; i++) {
                        cout << ZERO << endl;
                    }
                }
                
                if (symbols.front().to_int() < 4) {
                    bits_left = 8 - i;
                    leftover = symbols.front();
                    //cout << "bits_left: " << bits_left+0 << endl;
                }
            }
            //cout << "bits_left: " << bits_left+0 << endl;
            if (bits_left > 0 and symbols.size() == 1) {
                uint8_t count = 0;
                for (uint8_t j = 0; j < bits_left; j++) {
                    if ((leftover & 1).to_int()) {
                        count += pow(2, j);
                    }
                    leftover >>= 1;
                }
                cout << constellation.at(gc.at(count)) << endl;
            }
        }
        
        else {
            for (uint8_t i = 0; i < 8 / K; i++) {
                uint8_t count = 0;
                
                for (uint8_t j = 0; j < K; j++) {
                    if ((symbols.front() & 1).to_int()) {
                        count += pow(2, j);
                    }
                    symbols.front() >>= 1;
                }
                
                cout << constellation.at(gc.at(count)) << endl;
                
                for (int8_t i = 0; i < SAMPLES_PER_SYMBOL - 1; i++) {   //print out (0,0) 
                    cout << ZERO << endl;                               //(SAMPLES_PER_SYMBOL - 1) times
                }
            }
        }
        /*
        if (DEBUG) {
            while (!symbols.empty()) {
                symbols.pop();
            }
            exit(EXIT_SUCCESS);
        }*/
        symbols.pop();
    }
}
