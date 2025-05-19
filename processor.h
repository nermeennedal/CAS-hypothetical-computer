#ifndef Processor_H
#define Processor_H

#include <iostream>
#include <string>
#include "convert.h"
#include "memory.h"

using namespace std;
class processor {
	public:
		string opcode;
		string A, X, L, PC, SW, B, S, T, F;//Register for design
		string operand1, operand2,nixbpe;
		processor();
		~processor();

		void initialization();
		string register_design(string bins);
		void resgister_set(string value,string bins);



};
#endif Processor
