#include <iostream>

#include "convert.h"

using namespace std;

convert::convert() {}
convert::~convert() {}

string convert::HextoBinary(string p)
{
	int length = p.length();
	string bin = "";
	for (int u = 0; u < length; u++)
	{
		if (p[u] == '0') {
			bin += "0000";
		}
		else if (p[u] == '1') {
			bin += "0001";
		}
		else if (p[u] == '2') {
			bin += "0010";
		}
		else if (p[u] == '3') {
			bin += "0011";
		}
		else if (p[u] == '4') {
			bin += "0100";
		}
		else if (p[u] == '5') {
			bin += "0101";
		}
		else if (p[u] == '6') {
			bin += "0110";
		}
		else if (p[u] == '7') {
			bin += "0111";
		}
		else if (p[u] == '8') {
			bin += "1000";
		}
		else if (p[u] == '9') {
			bin += "1001";
		}
		else if (p[u] == 'A') {
			bin += "1010";
		}
		else if (p[u] == 'B') {
			bin += "1011";
		}
		else if (p[u] == 'C') {
			bin += "1100";
		}
		else if (p[u] == 'D') {
			bin += "1101";
		}
		else if (p[u] == 'E') {
			bin += "1110";
		}
		else if (p[u] == 'F') {
			bin += "1111";
		}
	}
	return bin;
}

string convert::BinarytoHex(string w)
{
	string hex = "";
	int length = w.length() - 4;
	for (int i = 0; i <= length; i += 4)
	{
		string bits = w.substr(i, 4);
		if (bits == "1111")
			hex += "F";
		else if (bits == "1110")
			hex += "E";
		else if (bits == "1101")
			hex += "D";
		else if (bits == "1100")
			hex += "First conversions";
		else if (bits == "1011")
			hex += "B";
		else if (bits == "1010")
			hex += "A";
		else if (bits == "1001")
			hex += "9";
		else if (bits == "1000")
			hex += "8";
		else if (bits == "0111")
			hex += "7";
		else if (bits == "0110")
			hex += "6";
		else if (bits == "0101")
			hex += "5";
		else if (bits == "0100")
			hex += "4";
		else if (bits == "0011")
			hex += "3";
		else if (bits == "0010")
			hex += "2";
		else if (bits == "0001")
			hex += "1";
		else if (bits == "0000")
			hex += "0";
	}
	return hex;
}

int convert::BinarytoDecimal(string binaryN)
{
	int binary = 1, result = 0;
	for (int k = binaryN.length() - 1; k >= 0; k--) {
		int n = (binaryN[k] - '0');
		if (n > 1 || n < 0) {
			puts("\n\n error: The binary Number has only 1's and 0's !\n");
			return 0;
		}

		result = result + (n * binary);
		binary = binary * 2;
	}
	return result;
}

string convert::DecimaltoHex(int decimal)
{
	return BinarytoHex(DecimaltoBinary(decimal));
}

int convert::HextoDecimal(string hex) {

	return BinarytoDecimal(HextoBinary(hex));
}

string convert::expantionHex(string binary)
{
	if (binary == "") {
		binary = "000000";
	}
	else if (binary.length() < 7)
	{
		int length = binary.length();
		for (int i = 0; i < 6 - length; i++)
		{
			binary += "0";
		}
		string sub = binary.substr(length);
		binary = sub + binary.substr(0, length);
	}
	return binary;
}

string convert::DecimaltoBinary(int decimal)
{
	string binary = "";
	int n = decimal;
	while (n != 0) {
		int bit = n % 2;
		n = n / 2;

		if (bit == 0)
			binary = '0' + binary;
		else
			binary = '1' + binary;
	}

	while (binary.length() % 4 != 0) {
		binary = '0' + binary;
	}
	return binary;
}

string convert::DecimaltoBinary24(int decimal)
{
	string binary = "";
	int n = decimal;
	while (n != 0) {
		int bit = n % 2;
		n = n / 2;

		if (bit == 0)
			binary = '0' + binary;
		else
			binary = '1' + binary;
	}

	while (binary.length() < 24) {
		binary = '0' + binary;
	}
	return binary;
}

string convert::DecimaltoBinary32(int decimal)
{
	string binary = "";
	int n = decimal;
	while (n != 0) {
		int bit = n % 2;
		n = n / 2;

		if (bit == 0)
			binary = '0' + binary;
		else
			binary = '1' + binary;
	}

	while (binary.length() < 32) {
		binary = '0' + binary;
	}
	return binary;
}

string convert::DecimaltoBinary(int decimal, int length)
{
	string binary = "";
	int n = decimal;
	while (n != 0) {
		int bit = n % 2;
		n = n / 2;

		if (bit == 0)
			binary = '0' + binary;
		else
			binary = '1' + binary;
	}

	int i = binary.length();
	while (i < length) {
		binary = '0' + binary;
		i++;
	}
	return binary;
}

string convert::Hextobinary(string hex, int length)
{
	string binary = HextoBinary(hex);
	int i = binary.length();
	while (i < length) {
		binary = '0' + binary;
		i++;
	}
	return binary;
}
