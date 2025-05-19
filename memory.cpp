#include "memory.h"

#include <iostream>
#include <fstream>

convert convertor1;
using namespace std;
memory::memory() {
	data = new string[1048576];
}
memory::~memory() {
	delete[]memory1;
	data = nullptr;
}
void memory::read_File() {
	
	ifstream file_read("Simulator Memory Input.txt");

	if (file_read.is_open()) {

		string word;

		bool found = false;

		while (!found) {
			string str = "START";
			file_read >> word;
			if (word == str) {
				cout << "word is " << word << endl;
				found = true;
			}
		}

		if (word == "START") {
			file_read >> word >> startaddress;
			cout << "start_address = " << startaddress << endl;

			startprogram = convertor1.BinarytoDecimal(convertor1.HextoBinary(startaddress));
		}

		bool found2 = false;
		string word2;

		while (!found2) {
			string str = "LAST";

			file_read >> word2;
			if (word2 == str) {
				cout << "word is " << word2 << endl;
				found2 = true;
			}
		}

		if (word2 == "LAST") {
			file_read >> word2 >> endaddress;
			cout << "end address" << endaddress << endl;
			endprogram = convertor1.BinarytoDecimal(convertor1.HextoBinary(endaddress));
		}

		string token;
		token = checkReading(file_read, "instructions");
		if (token == "instructions")
		{
			int addressCounter = startprogram;
			while (!file_read.eof()) {
				file_read >> token;
				string hexValue = "";
				int length = token.length();
				for (int j = 0; j < length; ++j) {
					if (token[j] != '_') {
						hexValue += token[j];
					}
				}
				length = hexValue.length();
				for (int k = 0; k < length; k += 2) {
					data[addressCounter] += hexValue.substr(k, 2);
					addressCounter++;
				}
			}
		}

	}
	else {
		cout << "wrong: file is not exist " << endl;
	}

}
string memory::checkReading(ifstream& myfile, string word) {
	string token = "";
	while (!myfile.eof()) {
		myfile >> token;
		if (token == word) {
			return token;
		}
	}
	return "";
}

void memory::print_File() {
	for (int i = startprogram; i <= endprogram; i++) {
		cout << data[i];

		cout << "_" << data[++i];

		cout << "_" << data[++i] << endl;
	}
	cout << "Check the output text file for your desired output" << endl;
}