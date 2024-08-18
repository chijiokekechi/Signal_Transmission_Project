#ifndef GRAY_CODE_HPP
#define GRAY_CODE_HPP

#include <cstdint>
#include <string>
#include <map>
#include <deque>
#include <complex>

using namespace std;

typedef map<uint16_t, uint16_t> gray_code_t;
typedef deque<complex<double>> constellation_t;

void encode (uint16_t, string, gray_code_t&, constellation_t&);
void gray_code (uint16_t, gray_code_t&);
void psk_constellation (uint16_t, constellation_t&);

#endif
