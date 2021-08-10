// ConsoleApplication9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

unsigned pack_bytes(string& bits, string& bytes) {
	char temp = (char)0;

	for (unsigned i = 0; i < bits.size(); i++) {
		if ((i + 1) % 8 == 0) {
			temp = (temp << 1) | (bits[i] & 0x01);
			bytes = bytes + (char)temp;
			cout << "byte: 0x" << setw(2) << hex << (short)((unsigned char)temp) << endl;
			temp = (char)0;
		}
		else {
			temp = (temp << 1) | (bits[i] & 0x01);
		}
	}

	if (bits.size() % 8)             // if there are leftover bits
		bytes = bytes + (char)temp; // append any remaining bits in the last byte

	return bytes.size();         // return number of bytes packed
}

unsigned unpack_bytes(string& bytes, string& ubits) {
	for (unsigned i = 0; i < bytes.size(); i++) {
		for (int j = 7; j >= 0; j--) {

			if (bytes[i] & (0x01) << j)
				ubits += '1';
			else
				ubits += '0';

			cout << "debug char " << ubits[ubits.size() - 1] << endl;

			//ubits.push_back( (char)(0x30 | (0x01 & (bytes[i] >> j))));
			//ubits = ubits + (char)(0x30 | (0x01 & (bytes[i] >> j)));
			//cout << "debug char " << hex << (short)((unsigned char)(0x30 | (0x01 & (bytes[i] >> j)))) << " j = " << j << endl;
		}
	}
	return ubits.size();   // return number of bits unpacked
}

int main()
{
	string bits = "100100101011111001011000";
	string bytes;
	string ubits;
	unsigned bitcnt = 0;
	unsigned bytecnt = 0;

	bytes.clear();
	ubits.clear();

	cout << "Test bit packing and unpacking" << endl;
	cout << "Original bit stream length = " << bits.size() << " bits: " << bits << endl << endl;

	bytecnt = pack_bytes(bits, bytes);
	cout << "bytes packed = " << bytecnt << endl;

	bitcnt = unpack_bytes(bytes, ubits);
	cout << "Unpacked bit stream length = " << bitcnt << " ubits.size = " << ubits.size() << " bits: " << ubits << endl << endl;

	return 1;
}