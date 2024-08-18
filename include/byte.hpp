#ifndef byte_t_hpp
#define byte_t_hpp

#include <cstdint>
#include <bitset>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

/*
 * Name: byte_t
 * Purpose: This is a class that represents an 8-bit value as just a byte. The idea of it is to be a
 *          better implementation of std::byte defined in the C++ 17 standard, implemented as a
 *          regular class instead of an enumerated class, which was just a weird way to implement a
 *          data structure like this. This is essentially a wrapper around an unsigned 8-bit integer
 *          (an unsigned character) with only the bitwise operations overloaded and defined for it.
 *          Also defined for this class are the assignment operator to allow for easier assignments,
 *          private functions to get and set the value of the underlying unsigned character, and
 *          functions to "convert" and get the underlying value of the byte as either an unsigned
 *          character or an unsigned 16-bit integer.
 */
class byte_t {
    private:
        uint8_t val;
        
        void set_value (uint8_t);
        uint8_t get_value () const;
        
    public:
        /*
         * Name: byte_t (default constructor, public)
         * Purpose: Default constructor for the byte_t class for no arguments. Does nothing.
         */
        byte_t () {}
        byte_t (const uint8_t);
        /*
         * Name: ~byte_t (default destructor, public)
         * Purpose: Default (and only) destructor for the byte_t class. Does nothing.
         */
        ~byte_t () {}
        
        uint16_t to_int () const;
        unsigned char to_char () const;
        
        // assignment operators
        void operator = (const byte_t);
        void operator = (const uint8_t);
        
        // bitwise AND operations
        byte_t operator & (const byte_t rhs);
        void operator &= (const byte_t rhs);
        
        // bitwise OR operators
        byte_t operator | (const byte_t rhs);
        void operator |= (const byte_t rhs);
        
        // bitwise XOR operators
        byte_t operator ^ (const byte_t rhs);
        void operator ^= (const byte_t rhs);
        
        // bitwise NOT operator
        byte_t operator ~ ();
        
        // bit shift right operations
        byte_t operator >> (const uint8_t rhs);
        void operator >>= (const uint8_t rhs);
        
        // bit shift left operations
        byte_t operator << (const uint8_t rhs);
        void operator <<= (const uint8_t rhs);
        
        friend ostream& operator << (ostream& os, const byte_t rhs);
        friend istream& operator >> (istream & is, byte_t & rhs);
};

#endif
