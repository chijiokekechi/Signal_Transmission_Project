
#include <iostream>
#include <complex>
#include <deque>
#include <vector>

using namespace std;

//this script will listen for the sync word which was generated on the transmitting side. 
//Once the sync word has been found, this will initiate the start of the packet, so then the next x bytes will be considered as a packet

//add function to take the next x bytes after sync word is recieved as a packet
void receivePacket(int packetSizeSymbols, int samplesPerSymbol)
{
    std::deque<complex<float>> sampleBuffer;

    complex<float> sample;

    for (int i = 0; i < packetSizeSymbols ; i++){
        for (int j = 0; j < samplesPerSymbol; j++) {
            std::cin >> sample;
            // cout << sample; // Testing only
            if (j == 7) {
                sampleBuffer.push_back(sample);
            }
        }
    }

    for (int i = 0 ; i < packetSizeSymbols ; i++)
        {
            cout << sampleBuffer[i];
        }
       
    sampleBuffer.clear();
}

float filter(std::deque<complex<float>> rxBuffer, std::deque<complex<float>> fC, int bufferSize)
{
    std::complex<float> output = 0;
    float magnitude = 0;

    for (int i = 0 ; i < bufferSize; i++)
    {
        output += rxBuffer[i]*std::conj(fC[bufferSize - 1 - i]);
    }

    magnitude = std::real(output*std::conj(output));

    return magnitude;
}

int main(){

    int bufferSize = 8*8*6;

    int packetSizeBytes = 256;
    int bitsPerSymbol = 1;
    int packetSizeBits = packetSizeBytes*8;
    int packetSizeSymbols = packetSizeBits*bitsPerSymbol;

    // TODO: Make samples per symbol an argument
    int samplesPerSymbol = 8;

    std::deque<complex<float>> byteBuffer;

    //buffer to hold the incoming bytes
    std::deque<complex<float>> rxBuffer(8*8*6, 0);

    // 0 -> {1, 0}
    // 1 -> {-1, 0}
    // UUAAUU BPSK mapping
    vector<complex<float>> fC= {{1, 0}, {-1, 0}, {1, 0} , {-1, 0}, {1, 0}, {-1,0}, {1, 0}, {-1, 0},
                                {1, 0}, {-1, 0}, {1, 0} , {-1, 0}, {1, 0}, {-1,0}, {1, 0}, {-1, 0},
                                {1, 0}, {-1, 0}, {1, 0} , {1, 0}, {1, 0}, {1, 0}, {1, 0}, {-1, 0},
                                {1, 0}, {-1, 0}, {1, 0} , {1, 0}, {1, 0}, {1, 0}, {1, 0}, {-1, 0},
                                {1, 0}, {-1, 0}, {1, 0} , {-1, 0}, {1, 0}, {-1,0}, {1, 0}, {-1, 0},
                                {1, 0}, {-1, 0}, {1, 0} , {-1, 0}, {1, 0}, {-1,0}, {1, 0}, {-1, 0}};

    std::deque<complex<float>> upsampledfC(8*8*6, 0);
    for (int i=0; i < 8*6; i++) {
        upsampledfC[i*samplesPerSymbol] = fC[i];
    }


    complex<float> sample;
    int idx = 0;

    while (true){
        idx ++;

        //read sample from stdin
        std::cin >> sample;
        // cout << sample << endl;

        // cerr << idx << endl;
        if(cin.eof())
            break;

        rxBuffer.push_back(sample);
        rxBuffer.pop_front();

        // filter(rxBuffer, upsampledfC, bufferSize);
        if(filter(rxBuffer, upsampledfC, bufferSize) > 1750){
            receivePacket(packetSizeSymbols, samplesPerSymbol);
            // cerr << "FOUND PACKET!" << endl;
        }

    }
    // cerr << idx << endl;
}
