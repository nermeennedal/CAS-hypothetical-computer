#ifndef MEMORY_H
#define MEMORY_H
#include <string>
#include "convert.h"

using namespace std;

class memory {
public:

	string* data;
	string memory1[2048];

	int PC_Counter, startprogram, endprogram;
	string startaddress, endaddress;

	memory();
	~memory();

	void read_File();
	string checkReading(ifstream& myfile, string word);
	void print_File();
};
#endif
