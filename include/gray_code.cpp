#include "gray_code.hpp"
#include <cctype>   //tolower
#include <cmath>

/*
 * Name: encode
 * Purpose: Provides a Gray encoding for the specified size and modulation type along with it's associated
 *          complex numbered constellation values.
 * NOTE: If other modulation types are to be included (e.g. PAM, QAM), automating the Gray encoding
 *       mechanism might need to be more complicated. This is currently only done with PSK in mind.
 */
void encode (uint16_t size, string modulation, gray_code_t & gray, constellation_t & constellation)
{
    gray_code(size, gray);
    
    for (uint8_t i = 0; i < modulation.length(); i++) {
        modulation[i] = tolower(modulation[i]);
    }
    
    if (modulation == "psk") {
        psk_constellation(size, constellation);
    }
}

/*
 * Name: gray_code
 * Purpose: Constructs a Gray encoding corresponding to the specified size. The size is currently assumed
 *          to be a power of 2. Encoding is done using the reflect and prefix method.
 * Source: https://www.tutorialspoint.com/conversion-of-binary-to-gray-code
 */
void gray_code (uint16_t size, gray_code_t & gray_code)
{
    uint8_t bits = log2(size);   //Assumes size is a power of 2
    gray_code[0] = 0;
    gray_code[1] = 1;
    
    for (uint8_t i = 1; i < bits; i++) {
        uint8_t reflect = gray_code.size(),
                prefix = gray_code.size();
        for (uint8_t j = prefix; j >= 1; j--) {
            gray_code[reflect] = gray_code[j - 1];
            gray_code[reflect] |= prefix;
            reflect++;
        }
    }
}

/*
 * Name: psk_constellation
 * Purpose: Returns the complex-valued PSK constellation corresponding to the specified size. The size is
 *          currently assumed to be a power of 2.
 */
void psk_constellation (uint16_t size, constellation_t & constellation)
{
    const double PI = acos(-1);
    //TODO: This isn't a huge worry, but the points where there should be a zero are actually just a
    //      really small number that shows up as 0 when printing in fixed-point notation. This is just
    //      a weired round off error thing, but it should probably be fixed to be set to zero at some
    //      point.
    if (size % 2 == 0) {
        if (size == 4) {
            const double OFFSET = PI / size;
            for (uint8_t i = 0; i < size; i++) {
                double symbol_location = (2 * i + 1) * OFFSET;
                constellation.push_back(complex<double>(cos(symbol_location), sin(symbol_location)));
            }
        }
        else {
            const double OFFSET = 2 *  PI / size;
            for (uint16_t i = 0; i < size; i++) {
                double symbol_location = i * OFFSET;
                constellation.push_back(complex<double>(cos(symbol_location), sin(symbol_location)));
            }
        }
    }
    else {
        constellation.push_back(complex<double>(0, 0));
    }
}
