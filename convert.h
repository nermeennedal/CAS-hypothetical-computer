#ifndef CONVERT_H
#define CONVERT_H

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class convert {
public:
    convert();
    ~convert();

    string HextoBinary(string hex);
    string BinarytoHex(string binary);
    int BinarytoDecimal(string binaryN);
    string DecimaltoBinary(int decimal);
    string DecimaltoBinary(int decimal, int length);
    string DecimaltoBinary24(int decimal);
    string DecimaltoBinary32(int decimal);
    int HextoDecimal(string hex);
    string DecimaltoHex(int decimal);
    string expantionHex(string binary);
    string Hextobinary(string hex, int length);
};

#endif // CONVERT_H
