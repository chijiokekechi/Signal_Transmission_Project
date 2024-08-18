#include <iostream>
#include <complex>
#include <deque>

using namespace std;

//this script will take in raw binary data in byte form and assemble this data into a packet 
//only once the packet has been filled will the data transmit


//this function fills the buffer with the sample most recently collected
void fillPacket(std::deque<unsigned char>& byteBuffer, const unsigned char sample)
{
    byteBuffer.push_front(sample);
}

void checkLength(std::deque<unsigned char>& byteBuffer, const int packetSize)
{
    int bufferLength = byteBuffer.size();

    cout << bufferLength << endl;

    if(bufferLength >= packetSize)
    {
        for (int i = 0 ; i < packetSize ; i++)
        {
            cout << byteBuffer[i];
        }
       
        byteBuffer.clear();
    } 
}

int main()
{
    //determines the size of the packet that will be transmited 
    int packetSize = 256;

    std::deque<unsigned char> byteBuffer;

    unsigned char sample;

    while (true){

        //read sample from stdin
        std::cin >> sample;

        if(cin.eof())
            break;

        fillPacket(byteBuffer, sample);

        checkLength(byteBuffer, packetSize);
    }
}