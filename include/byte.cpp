#include "byte.hpp"

using namespace std;

/*
 * Name: byte_t (constructor, public)
 * Purpose: Constructs the byte_t class by passing its argument to set_value, effectively assigning
 *          the argument to the wrapped unsigned 8-bit integer.
 */
byte_t::byte_t (const uint8_t val)
{
    //TODO: This will probably need some form of error checking for any # not between 0 - 255
    this->set_value(val);
}

/*
 * Name: set_value (private)
 * Purpose: Assigns its argument to the value of the wrapped unsigned 8-bit integer.
 */
void byte_t::set_value (uint8_t val)
{
    this->val = val;
}

/*
 * Name: get_value (private)
 * Purpose: Returns the value of the wrapped unsigned 8-bit integer. Must externally be called by
 *          either to_int or to_char (because private).
 */
uint8_t byte_t::get_value () const
{
    return val;
}

/*
 * Name: to_int (public)
 * Purpose: Calls get_value to retrieve the value of the wrapped unsigned 8-bit integer. That value is
 *          returned as a "converted" 16-bit integer. This is mainly due to possible confusion if
 *          needing to print the value directly after a call to this function (i.e. trying to directly
 *          print the actual unsigned 8-bit integer with cout will cause it to act like a character
 *          because that's what it actually is); this ensures that printing directly from a call to
 *          this function will display the actual integer value. Casting directly back to an unsigned
 *          8-bit integer won't affect anything because the most significant 8 bits will all be zero
 *          anyway.
 */
uint16_t byte_t::to_int () const
{
    return static_cast<uint16_t>(this->get_value());
}

/*
 * Name: to_char (public)
 * Purpose: Calls get_value to retrieve the value of the wrapped unsigned 8-bit integer and returns
 *          the value as a "converted" unsigned character. This effectively just "passes the baton",
 *          but is necessary to keep get_value as a private function and makes it easier on the user
 *          by having separate character and integer "conversion" functions.
 */
unsigned char byte_t::to_char () const
{
    return this->get_value();
}

/*
 * Name: Overloaded assignment operator (public)
 * Purpose: Assigns the value of the right-hand side (another byte) as the value of the byte on the
 *          left-hand side.
 */
void byte_t::operator = (const byte_t rhs)
{
    this->set_value(rhs.to_char());
}

/*
 * Name: Overloaded assignment operator (public)
 * Purpose: Assigns the right-hand side (an unsigned 8-bit integer) as the value of the byte on the
 *          left-hand side.
 */
void byte_t::operator = (const uint8_t rhs)
{
    this->set_value(rhs);
}

/*
 * Name: Overloaded bitwise AND operator (public)
 * Purpose: Performs bitwise AND between the left-hand side and right-hand side (both bytes). The
 *          result is returned as a byte. If an unsigned 8-bit integer or an unsigned char are passed
 *          as arguments instead, they will be automatically converted to a byte before the operation
 *          is performed.
 */
byte_t byte_t::operator & (const byte_t rhs)
{
    return byte_t (this->get_value() & rhs.to_char());
}

/*
 * Name: Overloaded bitwise AND-assign operator (public)
 * Purpose: Performs bitwise AND between the left-hand side and right-hand side (both bytes). The
 *          result is then assigned as the value of the left-hand side. If an unsigned 8-bit integer
 *          or an unsigned char are passed as arguments instead, they will be automatically converted
 *          to a byte before the operation is performed.
 */
void byte_t::operator &= (const byte_t rhs)
{
    this->set_value(this->get_value() & rhs.to_char());
}

/*
 * Name: Overloaded bitwise OR operator (public)
 * Purpose: Performs bitwise OR between the left-hand side and right-hand side (both bytes). The
 *          result is returned as a byte. If an unsigned 8-bit integer or an unsigned char are passed
 *          as arguments instead, they will be automatically converted to a byte before the operation
 *          is performed.
 */
byte_t byte_t::operator | (const byte_t rhs)
{
    return byte_t (this->get_value() | rhs.to_char());
}

/*
 * Name: Overloaded bitwise OR-assign operator (public)
 * Purpose: Performs bitwise OR between the left-hand side and right-hand side (both bytes). The
 *          result is then assigned as the value of the left-hand side. If an unsigned 8-bit integer
 *          or an unsigned char are passed as arguments instead, they will be automatically converted
 *          to a byte before the operation is performed.
 */
void byte_t::operator |= (const byte_t rhs)
{
    this->set_value(this->get_value() | rhs.to_char());
}

/*
 * Name: Overloaded bitwise XOR operator (public)
 * Purpose: Performs bitwise XOR between the left-hand side and right-hand side (both bytes). The
 *          result is returned as a byte. If an unsigned 8-bit integer or an unsigned char are passed
 *          as arguments instead, they will be automatically converted to a byte before the operation
 *          is performed.
 */
byte_t byte_t::operator ^ (const byte_t rhs)
{
    return byte_t (this->get_value() ^ rhs.to_char());
}

/*
 * Name: Overloaded bitwise XOR-assign operator (public)
 * Purpose: Performs bitwise OR between the left-hand side and right-hand side (both bytes). The
 *          result is then assigned as the value of the left-hand side. If an unsigned 8-bit integer
 *          or an unsigned char are passed as arguments instead, they will be automatically converted
 *          to a byte before the operation is performed.
 */
void byte_t::operator ^= (const byte_t rhs)
{
    this->set_value(this->get_value() ^ rhs.to_char());
}

/*
 * Name: Overloaded bitwise NOT operator (public)
 * Purpose: Performs bitwise NOT between the left-hand side and right-hand side (both bytes). The
 *          result is returned as a byte. If an unsigned 8-bit integer or an unsigned char are passed
 *          as arguments instead, they will be automatically converted to a byte before the operation
 *          is performed.
 */
byte_t byte_t::operator ~ ()
{
    return byte_t (~this->get_value());
}

/*
 * Name: Overloaded bitwise shift right operator (public)
 * Purpose: Performs bitwise right shift on the left-hand side (a byte) by a number of bits equal to
 *          the right-hand side (an unsigned 8-bit integer). The result is returned as a byte.
 */
byte_t byte_t::operator >> (const uint8_t rhs)
{
    return byte_t (this->get_value() >> rhs);
}

/*
 * Name: Overloaded bitwise shift right-assign operator (public)
 * Purpose: Performs bitwise right shift on the left-hand side (a byte) by a number of bits equal to
 *          the right-hand side (an unsigned 8-bit integer). The result is then assigned as the value
 *          of the left-hand side.
 */
void byte_t::operator >>= (const uint8_t rhs)
{
    this->set_value(this->get_value() >> rhs);
}

/*
 * Name: Overloaded bitwise shift left operator (public)
 * Purpose: Performs bitwise left shift on the left-hand side (a byte) by a number of bits equal to
 *          the right-hand side (an unsigned 8-bit integer). The result is returned as a byte.
 */
byte_t byte_t::operator << (const uint8_t rhs)
{
    return byte_t (this->get_value() << rhs);
}

/*
 * Name: Overloaded bitwise shift left-assign operator (public)
 * Purpose: Performs bitwise left shift on the left-hand side (a byte) by a number of bits equal to
 *          the right-hand side (an unsigned 8-bit integer). The result is then assigned as the value
 *          of the left-hand side.
 */
void byte_t::operator <<= (const uint8_t rhs)
{
    this->set_value(this->get_value() << rhs);
}

/*
 * Name: Overloaded output stream operator (public, friend)
 * Purpose: When this operator is used with a byte (right-hand side), the byte is converted to a
 *          string representation (in binary) of its wrapped 8-bit value for display to stdout or for
 *          writing to a file.
 */
ostream& operator << (ostream& os, const byte_t rhs)
{
    return os << bitset<8>(rhs.get_value());
}

/*
 * Name: Overloaded input stream operator (public, friend)
 * Purpose: When this operator is used with a byte (right-hand side), the byte is assigned the value
 *          of the right hand side either from user input or from a file. This function first attempts
 *          to detect if the user entered in a character or an integer and reacts accordingly to
 *          properly assign the byte to the input value. If the user puts in something invalid (e.g. a
 *          string of multiple character or multiple characters and numbers), an invalid_argument
 *          exception is thrown; this will catch that exception, print out an error message, and
 *          promptly exit the program.
 * NOTE: If the user enters in a number greater than 255, it appears that the value is automatically
 *       reduced to a value within the range an unsigned 8-bit value can hold via a modulo 256
 *       operation (e.g. entering in a value of 260 will assign a value of 4 to the byte).
 * TODO: This has only been tested with stdin and appears to work correctly. It still needs to be
 *       tested with input from a file and with piped input if the need for that ever arises.
 */
istream& operator >> (istream & is, byte_t & rhs)
{
    string str;
    getline(cin, str);
    
    try {
        if (str.length() == 1 and !isdigit(str.front())) {
            rhs.set_value(str.front());
        }
        else {
            rhs.set_value(stoi(str));
        }
    }
    catch (invalid_argument exc) {
        cerr << endl
             << "Whatever input you gave is wrong and would be more than one byte anyway. "
             << "Stop being dumb." << endl
             << endl;
        exit(EXIT_FAILURE);
    }
    
    return is;
}
