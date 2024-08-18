#include <iostream>
#include <vector>


// converts a char (one byte) into a vector of 8 bits that can be easily indexed
// bit 0 is the LSB, bit 7 is the MSB
std::vector<bool> byte2bits(const unsigned char byte){
    int N_bits = 8;
    std::vector<bool> out(N_bits, 0);
    for (int n = 0; n < N_bits; n++){
        out[n] = static_cast<bool>((byte >> n) & 1);
    }
    return out;
}

int main(){

    char byte;
    std::vector<bool> bits(8, 0);

    while (true) {
        std::cin.get(byte); // reads one byte from stdin and stores it
        bits = byte2bits(byte); // converts the byte into a bit vector of length 8

        // print bits to the screen, one byte at a time
        // printing them in the order MSB......LSB to match normal reading order
        for (int n = 7; n >= 0; n--) {
            std::cout << bits[n];
        }
        std::cout << std::endl;

        // end program once file has been read (eof means "end of file")
        if (std::cin.eof()){
            break;
        }
    }

    std::cout << std::endl;

    return 0;
}
