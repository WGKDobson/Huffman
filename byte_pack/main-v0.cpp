#include <iostream>
#include <string>

using namespace std;

unsigned pack_bytes(string& bits, string& bytes){
    char temp = (char)0;

    for(unsigned i = 0; i < bits.size(); i++){
        if((i+1)%8 == 0){
            temp = (temp<<1)|(bits[i] & 0x01);
            bytes = bytes + (char)temp;
            cout << "byte: 0x" << hex << (unsigned)temp << endl;
            temp = (char)0;
        }
        else{
            temp = (temp<<1)|(bits[i] & 0x01);
        }
    }

    if(bits.size() % 8)             // if there are leftover bits
        bytes = bytes + (char)temp; // append any remaining bits in the last byte

    return bytes.size();         // return number of bytes packed
}

unsigned unpack_bytes(string& bytes,string& bits){
    for(unsigned i = 0; i < bytes.size(); i++){
        for(int j = 7; j >= 0; j--){
            bits = bits + (char)(0x30 | (0x01 & (bytes[i]>>j)));
            cout << "debug char " << (char)(0x30 | (0x01 & (bytes[i]>>j))) << endl;
        }
    }
    return bits.size();   // return number of bits unpacked
}

int main()
{
    string bits = "100100110011111001011000";
    string bytes;
    string ubits;
    unsigned bitcnt =0;
    unsigned bytecnt = 0;

    cout << "Test bit packing and unpacking"<<endl;
    cout << "Original bit stream length = "<< bits.size() << " bits: " << bits << endl << endl;

    bytecnt = pack_bytes(bits, bytes);
    cout << "bytes packed = " << bytecnt << endl ;

    bitcnt = unpack_bytes(bytes, ubits);
    cout << "Unpacked bit stream length = "<< bitcnt <<  " ubits.size = "<< ubits.size() << " bits: " << ubits << endl << endl;

    return 1;
}
