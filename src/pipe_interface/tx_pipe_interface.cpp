#include <iostream>
#include <complex>
#include <deque>

using namespace std;

//this script will take in raw binary data in byte form and assemble this data into a packet 
//only once the packet has been filled will the data transmit


//add function that generates a sync word here


//add function that generates the FEC here



//this function fills the buffer with the sample most recently collected
void fillPacket(std::deque<unsigned char>& byteBuffer, const unsigned char sample)
{
    byteBuffer.push_back(sample);
}

void checkLength(std::deque<unsigned char>& byteBuffer, const int packetSize)
{
    int bufferLength = byteBuffer.size();
    
    std::string syncword = "UUAAUU";

    if(bufferLength >= packetSize)
    {
        //add code to generate and send out the sync word to standard out
        cout << syncword;

        //add code to generate and send the forward error correction to standard out
        for (int i = 0 ; i < packetSize ; i++)
        {
            cout << byteBuffer[i];
        }
       
        byteBuffer.clear();
    } 
}

int main()
{
    //determines the size of the data packet that will be transmited 
    int packetSize = 256;

    std::deque<unsigned char> byteBuffer;

    unsigned char sample;

    while (true){

        //read sample from stdin
        std::cin >> sample;

        fillPacket(byteBuffer, sample);

        checkLength(byteBuffer, packetSize);
        
        if(cin.eof())
            // std::cout << sample;
            break;
    }
    std::cout << sample << std::endl;
}