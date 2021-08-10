/*********************
VGP310 Example code to pack or unpack a string sequence of '1' and '0'
into unsigned char bytes and to unpack bytes into the same bit string.
W. Dobson 1-28-18

**********************/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
/*********
Function packs bits string into bytes string and
returns the number of bytes packed.
**********/
unsigned pack_bytes(string& bits, string& bytes){
    unsigned char temp = (unsigned char)0;

    for(unsigned i = 0; i < bits.size(); i++){
        if((i+1)%8 == 0){   // if the count is at the byte boundary
            temp = (temp<<1)|(bits[i] & 0x01);   // add LSB
            bytes = bytes + (char)temp;     // append byte to the bytes string
            // prints 2 digit hex values. Sets the cout hex flag
            cout << "byte: 0x" << setw(2) << hex << (unsigned)temp << endl;
             // must clear hex mode for cout or all cout ints will be hex values
            cout.unsetf(ios::hex); // *** very important ***

            temp = (unsigned char)0;  // clear to build next byte
        }
        else{
            temp = (temp<<1)|(bits[i] & 0x01);  // add LSB
        }
    }

    if(bits.size() % 8)             // if there are leftover bits
        bytes = bytes + (char)temp; // append any remaining bits in the last byte

    return bytes.size();         // return number of bytes packed
}

/*********
Function unpacks bytes string into bits string of '1' and '0'
then returns the number of bits unpacked.
**********/
unsigned unpack_bytes(string& bytes,string& bits){
    for(unsigned i = 0; i < bytes.size(); i++){     // go through each byte
        for(int j = 7; j >= 0; j--){                // append 8 bits string per byte (char)
            bits = bits + (char)(0x30 | (0x01 & (bytes[i]>>j)));
            // note the use of ASCII hex code to make char: 0x30 == '0' and '0x31 == '1'
            //cout  <<"debug char " << (char)(0x30 | (0x01 & (bytes[i]>>j))) << endl;
        }
    }
    return bits.size();   // return number of bits unpacked
}

/*****************************/
int main()
{
    string bits = "100100110011111001011000";  // test bits string
    string bytes;
    string ubits;               // unpacked bits as a string
    unsigned bitcnt =0;
    unsigned bytecnt = 0;

    cout << "Test bit packing and unpacking"<<endl;
    cout << "Original bit stream length = "<< bits.size() << " bits: " << bits << endl << endl;

    bytecnt = pack_bytes(bits, bytes);
    cout << "bytes packed = " << bytecnt << endl ;

    bitcnt = unpack_bytes(bytes, ubits);
    cout << "Unpacked bit stream length = "<< bitcnt <<  " ubits.size = "<< ubits.size() << " bits: " << ubits << endl << endl;

    if(ubits.compare(bits) == 0)
        cout << "Unpacked bits match OK" << endl;
    else
        cout << "*** Unpacked bits mismatch! ***" << endl;

    return 1;
}
