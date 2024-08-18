#include "gray_code.hpp"
#include <cstdint>
#include <string>
#include <complex>
#include "byte.hpp"
#include <queue>

using namespace std;

/*
 * Name: decoder_t
 * Purpose: A class that instantiates a decoder object. The decoder object contains an associated Gray
 *          encoding scheme and constellation mapping that it uses to decode objects. The private
 *          setter functions are used to properly set the queue of symbols and the constellation for
 *          decoding so that symbols can be decoded. The function next is used to decode the next
 *          symbol. See decoder.cpp for more details on individual functions.
 */
class decoder_t {
    private:
        gray_code_t gc;
        constellation_t constellation;
        queue<complex<double>> * symbols;
        
        void set_symbols (queue<complex<double>>*);
        void set_constellation (double = 1e6);
    
    public:
        decoder_t (uint16_t, string, queue<complex<double>>*, double = 1e6);
        ~decoder_t ();
        byte_t next ();
};
