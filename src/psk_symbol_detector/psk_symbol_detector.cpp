// ECE 6710 - Communication System Theory - Spring 2022
// Implementing a PSK Symbol Detector 
// Assuming M-PSK Modulation 
#include <iostream>
#include <complex>
#include <vector>
#include <assert.h> // Verifies assumptions made by program 
#define PI 3.14159265358979

// Output as either symbols or bytes 
#define OUTPUT_AS_SYMBOLS 0
#define OUTPUT_AS_BYTES (!OUTPUT_AS_SYMBOLS)

using namespace std;

unsigned int BinaryToGray(unsigned int num)
{
    return num ^ (num >> 1); // XOR Operation 
}


#if OUTPUT_AS_BYTES
// Concatenate symbols to build up binary data:
void add_symbol_to_output(const int symbol, unsigned char &bb, vector<unsigned char> &output, const int bits_per_symbol, int &bitptr)
{
  // char bb is a running byte to receive this symbol

  unsigned int symbol_bitmask = 1L << (bits_per_symbol - 1); // bitmask for symbol
  unsigned int output_bitmask = 1L << bitptr; // current bitmask into bb
  for (int ii = bits_per_symbol - 1;ii >= 0;ii--)  // once for each bit in the symbol
  {
    // If there is a 1 in the spot, transcribe it to bb
    if (symbol & symbol_bitmask) bb = bb | output_bitmask;
    // Shift both bitmasks
    symbol_bitmask = symbol_bitmask >> 1;
    output_bitmask = output_bitmask >> 1;
    bitptr--;

    // If a full byte has been transcribed, save it and reset. 
    if (bitptr < 0)
    {
      // increase output
      output.resize(output.size() + 1);
      // Assign new byte to end
      output[output.size() - 1] = bb;
      // Reset index to current bb bit
      bitptr = 7;
      // Reset bitmask
      output_bitmask = 1L << bitptr;
      // Reset bb to 0
      bb = 0;
    }
  }
}
#endif


int main(int argc, char* argv[])
{
    // Parameters being Passed: 
    int symbol_period = 8;
    int bits_per_symbol = 3;
    int decision_time_offset = 5;

	// User Input: Command Line Argument section
    if (argc != 4)
    {
      cout << "Usage: " << argv[0] << " modulation_order samples_per_symbol decision_time_offset" << endl;
      return 1;
    }
    else
    {
      bits_per_symbol = stoi(argv[1]); // modulation_order
      symbol_period = stoi(argv[2]);  // samples_per_symbol
      decision_time_offset = stoi(argv[3]); // decision time offset 
    }

    // Calculate symbol_count from bits_per_symbol:
    int symbol_count = pow(2, bits_per_symbol);


#if OUTPUT_AS_BYTES // Has symbols combined into complete bytes 

    int byteptr = 0;
    int bitptr = 7;
    vector<unsigned char> rawdigitaloutput;
    unsigned char bb = 0;
#endif

// Decoding: 
    int decoded_symbol;
    // decoding will be done once every symbol period, offset by the decision_time_offset
    int count = -decision_time_offset;
    complex<float> filtered_rx_input;

    // run loop until the end of file 
    while (!cin.eof())
    {
      // try to load complex<float>  
      cin >> filtered_rx_input;
      if(cin.fail()) // Checks for errors 
      {
        cin.clear();
        cin.ignore();
      }
      else
      {
        // valid input, test for time to decode by using count mod symbol_period
        if ((count >= 0) && ((count%symbol_period) == 0))
        {
          // Decode the provided input:
          // Using arctan to provide the angle from the complex input 
          float angle = atan2(filtered_rx_input.imag(), filtered_rx_input.real());
		  
          // Normalizes angle if negative
          if (angle < 0) angle += 2*PI;  
          float normalized_angle = angle/(2*PI);
          decoded_symbol = round(normalized_angle*symbol_count); // Corresponds to the symbol to decode 

          decoded_symbol = decoded_symbol & (symbol_count - 1); // ANDing decoded_symbol with symbol_count - 1 

// Output Section: 
#if OUTPUT_AS_SYMBOLS
            cout << BinaryToGray(decoded_symbol) << endl;
#endif
#if OUTPUT_AS_BYTES
            add_symbol_to_output(BinaryToGray(decoded_symbol), bb, rawdigitaloutput, bits_per_symbol, bitptr);
#endif
#if DEBUG
            cout << filtered_rx_input << "symbol: " <<
              decoded_symbol << " graycode: " << BinaryToGray(decoded_symbol) << endl;
#endif
        }
        // Increment count for the next iteration:
        count++;
      }
    }
	// Outputs to stdout as Raw Bytes:
#if OUTPUT_AS_BYTES
  for(const auto& el: rawdigitaloutput) cout << "0x" << std::hex << int(el) << endl;
#endif

    return 0;
}
