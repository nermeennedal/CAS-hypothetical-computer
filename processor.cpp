
#include <iostream>
#include <string>
#include <fstream>
#include "processor.h"

using namespace std;

memory *mymem;
convert *conv;
processor::processor(){
	A = "000000000000000000000000";
	X = "000000000000000000000000";
	L = "000000000000000000000000";
	PC ="000000000000000000000000";
	SW ="000000000000000000000000";
	B = "000000000000000000000000";
	S = "000000000000000000000000";
	T = "000000000000000000000000";
	F = "000000000000000000000000";
	PC = "000000000000000000000000";
	mymem = new memory();
	mymem->read_File();
	mymem->print_File();
	conv = new convert();
	PC = conv->DecimaltoBinary(mymem->startprogram);
}

processor:: ~processor() {}

void processor::initialization() {
	int PCcon = mymem->startprogram;
	while ((PCcon >= (mymem->startprogram)) &&( PCcon <=(mymem->endprogram) ) ) {
		
		opcode = conv->HextoBinary(mymem->data[PCcon]);
		
		if (opcode.length() == 0) {
			continue;
		}
		opcode.replace(opcode.length()-2,2,"00");
		string instruction = "";
		string ahmad = "";
			//format 1
			if (opcode == "11000100") {//FIX
				instruction = mymem->data[PCcon];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 1);

				
			}
			else if (opcode == "11000000") {//FLOAT
			
			}
			//format 2
			else if (opcode == "10010000") {//ADDR r1,r2 instruction
			instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
			instruction = conv->HextoBinary(instruction);
			PC = conv->DecimaltoBinary24(PCcon+2);

			operand1 = instruction.substr(8, 4);
			operand2 = instruction.substr(12, 4);

			int r1 = conv->BinarytoDecimal(register_design(operand1));
			int r2 = conv->BinarytoDecimal(register_design(operand2));

			int addr = r1 + r2;
			resgister_set(conv->DecimaltoBinary24(addr),operand2);

			}
			else if (opcode == "10110100") {//clear r1 instruction
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon+2);

				operand1 = instruction.substr(8, 4);
				operand2 = instruction.substr(12, 4);

				string zero = "000000000000000000000000";
				resgister_set(zero, operand1);
			}
			else if (opcode == "10100000") {//compr r1,r2
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 2);

				operand1 = instruction.substr(8, 4);
				operand2 = instruction.substr(12, 4);

				int r1 = conv->BinarytoDecimal(register_design(operand1));
				int r2 = conv->BinarytoDecimal(register_design(operand2));
				if (r1<r2) {
					SW = "000000000000000000000000";
				}
				else if (r1 == r2) {
					SW = "000000100000000000000000";
				}
				else if (r1>r2) {
					SW = "000000110000000000000000";
				}
			}
			else if (opcode == "10011100") {//divr r1,r2
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 2);

				operand1 = instruction.substr(8, 4);
				operand2 = instruction.substr(12, 4);

				int r1 = conv->BinarytoDecimal(register_design(operand1));
				int r2 = conv->BinarytoDecimal(register_design(operand2));

				int divr = r1 / r2;
				resgister_set(conv->DecimaltoBinary24(divr), operand2);

			}
			else if (opcode == "10011000") {//mulr r1,r2
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 2);

				operand1 = instruction.substr(8, 4);
				operand2 = instruction.substr(12, 4);

				int r1 = conv->BinarytoDecimal(register_design(operand1));
				int r2 = conv->BinarytoDecimal(register_design(operand2));
	
				int mulr = r1 * r2;
				resgister_set(conv->DecimaltoBinary24(mulr), operand2);

			}
			else if (opcode == "10101100") {//RMO r1,r2
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 2);

				operand1 = instruction.substr(8, 4);
				operand2 = instruction.substr(12, 4);

				resgister_set(register_design(operand1), operand2);

			}
			else if (opcode == "10100100") {//SHIFTL r1,n}
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 2);
	
				operand1 = instruction.substr(8, 4);
				operand2 = instruction.substr(12, 4);

				string r1 = register_design(operand1);
				int n = conv->BinarytoDecimal(operand2);

				for (int i = 0; i < n; i++) {
					for (int j = 0; j < 24; j++) {
						char zero = '0';
						if (j < 23) {
							r1[j] = r1[j + 1];
						}
						else {
							r1[j] = zero;
						}
					}
					
				}
				resgister_set(r1,operand1);
			}
			else if (opcode == "10101000") {//SHIFTR r1,n}
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 2);

				operand1 = instruction.substr(8, 4);
				operand2 = instruction.substr(12, 4);

				string r1 = register_design(operand1);
				int n = conv->BinarytoDecimal(operand2);

				for (int i = 0; i < n; i++) {
					for (int j = 23; j >= 0; j--) {
						char zero = '0';
						if (j > 0) {
							r1[j] = r1[j-1];
						}
						else {
							r1[j] = zero;
						}
					}

				}
				resgister_set(r1, operand1);
			}
			else if (opcode == "10010100") {//SUBR r1,r2
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 2);

				operand1 = instruction.substr(8, 4);
				operand2 = instruction.substr(12, 4);

				int r1 = conv->BinarytoDecimal(register_design(operand1));
				int r2 = conv->BinarytoDecimal(register_design(operand2));

				int subr = r1 - r2;
				resgister_set(conv->DecimaltoBinary24(subr), operand2);

		}
			else if (opcode == "10111000") {//TIXR r1
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				PC = conv->DecimaltoBinary24(PCcon + 2);

				operand1 = instruction.substr(8, 4);
				 
				int value = conv->BinarytoDecimal(X) + 1;
				X = conv->DecimaltoBinary24(value);
				int r1 = conv->BinarytoDecimal(register_design(operand1));

				if (value < r1) {
					SW = "000000000000000000000000";
				}
				else if (r1 == value) {
					SW = "000000110000000000000000";
				}
				else if (value > r1) {
					SW = "000000110000000000000000";
				}
			}
			
			//format 3/4

			//ADD m
			else if (opcode == "00011000") {//ADD m 
				instruction = mymem->data[PCcon]+ mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);
				
				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
							
						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target])+ conv->HextoDecimal(mymem->data[target+1])+ conv->HextoDecimal(mymem->data[target+2]);
				A = conv->DecimaltoBinary24( value + conv->BinarytoDecimal(A) );
			}
			//ADDF m
			else if (opcode == "01011000") {//ADDF m

			}
			//AND m
			else if (opcode == "01000000") {//AND m
				instruction = mymem->data[PCcon]+ mymem->data[PCcon +1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) & conv->HextoDecimal(mymem->data[target + 1]) & conv->HextoDecimal(mymem->data[target + 2]);
				A = conv->DecimaltoBinary24(value & conv->BinarytoDecimal(A));
			}
			//COMP m
			else if (opcode == "00101000") {//COMP m
				instruction = mymem->data[PCcon ]+ mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) & conv->HextoDecimal(mymem->data[target + 1]) & conv->HextoDecimal(mymem->data[target + 2]);
				int A_value = conv->BinarytoDecimal(A);
				if (A_value < value) {
					SW = "000000000000000000000000";
				}
				else if (A_value == value) {
					SW = "000000100000000000000000";
				}
				else if (A_value > value) {
					SW = "000000110000000000000000";
				}

			}
			//COMPF m
			else if (opcode == "10001000") {//COMPF m

			}
			//DIV m
			else if (opcode == "00100100") {//DIV m
				instruction = mymem->data[PCcon]+ mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) & conv->HextoDecimal(mymem->data[target + 1]) & conv->HextoDecimal(mymem->data[target + 2]);
				A = conv->DecimaltoBinary24(conv->BinarytoDecimal(A)/value);
				
			}
			//DIVF m
			else if (opcode == "01100100") {//DIVF m

			}
			//J m
			else if (opcode == "00111100") {//J m
				instruction = mymem->data[PCcon ]+mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]);
				PC = conv->DecimaltoBinary24(value);
			}
			//JEQ m
			else if (opcode == "00110000") {//JEQ m
				instruction = mymem->data[PCcon]+ mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) ;
				if (SW== "000000100000000000000000") {
					PC = conv->DecimaltoBinary24(value);
				}
			}
			//JGT m
			else if (opcode == "00110100") {//JGT m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]);
				if (SW == "000000110000000000000000") {
					PC = conv->DecimaltoBinary24(value);
				}
			}
			//JLT m
			else if (opcode == "00111000") {//JLT m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]);
				if (SW == "000000000000000000000000") {
					PC = conv->DecimaltoBinary24(value);
				}
			}
			//JSUB m
			else if (opcode == "01001000") {//JSUB m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]);
				L = PC;
				PC = conv->DecimaltoBinary24(value);
			}
			//LDA m
			
			else if (opcode == "00000000") {//LDA m
				instruction = mymem->data[PCcon]+ mymem->data[PCcon+1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);
				
				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->HextoDecimal(instruction.substr(12,12));
					
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {

							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
							int target1 = conv->BinarytoDecimal(instruction.substr(12, 12));
							if (ni == "11") {
							target = target1 + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target])+ conv->HextoDecimal(mymem->data[target+1])+ conv->HextoDecimal(mymem->data[target+2]);
				A = conv->DecimaltoBinary24(value);
			}//error
			
			//LDB m
			else if (opcode == "01101000") {//LDB m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) + conv->HextoDecimal(mymem->data[target + 1]) + conv->HextoDecimal(mymem->data[target + 2]);
				B = conv->DecimaltoBinary24(value);
			}
			//LDL m
			else if (opcode == "00001000") {
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) + conv->HextoDecimal(mymem->data[target + 1]) + conv->HextoDecimal(mymem->data[target + 2]);
				L = conv->DecimaltoBinary24(value);
			}
			//LDS m
			else if (opcode == "01101100") {
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) + conv->HextoDecimal(mymem->data[target + 1]) + conv->HextoDecimal(mymem->data[target + 2]);
				S = conv->DecimaltoBinary24(value);
			}
			//LDT m
			else if (opcode == "01110100") {
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) + conv->HextoDecimal(mymem->data[target + 1]) + conv->HextoDecimal(mymem->data[target + 2]);
				T = conv->DecimaltoBinary24(value);
			}
			//LDX m
			else if (opcode == "00000100") {//LDX m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) + conv->HextoDecimal(mymem->data[target + 1]) + conv->HextoDecimal(mymem->data[target + 2]);
				X = conv->DecimaltoBinary24(value);
			}
			//MUL m
			else if (opcode == "00100000") {//MUL m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
							
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) + conv->HextoDecimal(mymem->data[target + 1]) + conv->HextoDecimal(mymem->data[target + 2]);
				A = conv->DecimaltoBinary24(conv->BinarytoDecimal(A) * value);
			}
			//MULF m
			else if (opcode == "01100000") {//MULF m 

			}
			//OR m
			else if (opcode == "01000100") {//OR m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) + conv->HextoDecimal(mymem->data[target + 1]) + conv->HextoDecimal(mymem->data[target + 2]);
				A = conv->DecimaltoBinary24(conv->BinarytoDecimal(A) | value);
			}
			//RD m
			else if (opcode == "11011000") {//RD m
				
				instruction = mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = instruction.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}
				string OLDdisp = "0";
				string nameio = "";

				string target1 = instruction;
				string disp = target1.substr(0, 8);
				
				if (disp != OLDdisp) {
					OLDdisp = disp;
					ifstream myfile("simulator IO Input.txt");
					if (myfile.is_open()) {
						while (!myfile.eof()) {
							getline(myfile, nameio);
							int pos = nameio.find("I/O '");
							if (pos != string::npos) {
								string io = nameio.substr(pos + 5, 2);
								A.replace(4, 2, io);
							}
						}
						myfile.close();
					}
					else {
						cout << "Error in reading simulator IO Input file!!";
					}
				}
			}
			//RSUB
			else if (opcode == "01001100") {//RSUB
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				PC = L;
			}
			//STA m
			else if (opcode == "00001100") {//STA m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);

				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				mymem->memory1[target] = conv->BinarytoHex(A.substr(0,8));
				mymem->memory1[target + 1] = conv->BinarytoHex(A.substr(8, 8));
				mymem->memory1[target + 2] = conv->BinarytoHex(A.substr(16, 8));
				
			}
			//STX m
			else if (opcode == "00010000") {//STX m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);
				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				mymem->memory1[target] = conv->BinarytoHex(X.substr(0, 8));
				mymem->memory1[target + 1] = conv->BinarytoHex(X.substr(8, 8));
				mymem->memory1[target + 2] = conv->BinarytoHex(X.substr(16, 8));
			}
			//SUB m
			else if (opcode == "00011100") {//SUB m
				instruction = mymem->data[PCcon] + mymem->data[PCcon + 1];
				instruction = conv->HextoBinary(instruction);
				nixbpe = instruction.substr(6, 6);
				string ni = nixbpe.substr(0, 2);
				int target = 0;
				//format 3
				if (nixbpe[5] == '0') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2];
					PC = conv->DecimaltoBinary24(PCcon + 3);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 12));
					//b=1
					if (nixbpe[3] == '1') {
						if (ni == "11") {
							target = target + conv->BinarytoDecimal(B);
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));

						}
						else if (ni == "01") {
							target = target + conv->BinarytoDecimal(B);

						}
						else if (ni == "10") {
							target = target + conv->BinarytoDecimal(B);
						}
					}//p=1
					else if (nixbpe[4] == '1') {
						if (ni == "11") {
							target = target + PCcon;
							if (nixbpe[2] == '1') {
								target = target + conv->BinarytoDecimal(X);
							}
						}
						else if (ni == "00") {
							target = conv->BinarytoDecimal(instruction.substr(9, 15));
						}
						else if (ni == "01") {
							target = target + PCcon;
						}
						else if (ni == "10") {
							target = target + PCcon;

						}
					}
				}//format 4
				else if (nixbpe[5] == '1') {
					instruction = mymem->data[PCcon] + mymem->data[PCcon + 1] + mymem->data[PCcon + 2] + mymem->data[PCcon + 3];
					PC = conv->DecimaltoBinary24(PCcon + 4);
					instruction = conv->HextoBinary(instruction);
					target = conv->BinarytoDecimal(instruction.substr(12, 20));
					
					if (ni == "11") {
						if (nixbpe[2] == '1') {
							target = target + conv->BinarytoDecimal(X);
						}
					}
				}

				int value = conv->HextoDecimal(mymem->data[target]) + conv->HextoDecimal(mymem->data[target + 1]) + conv->HextoDecimal(mymem->data[target + 2]);
				A = conv->DecimaltoBinary24(conv->BinarytoDecimal(A) - value);
			}
			//SUBF m
			else if (opcode == "01011100") {//SUBF m

			}
			
			PCcon = conv->BinarytoDecimal(PC);

	}
	PC = conv->DecimaltoBinary24(PCcon);
	//print output file
	ofstream outPut("Simulator Output.txt");
	if (outPut.is_open()) {
		outPut << "!! Registers\n";
		outPut << "A = " << conv->BinarytoHex(A) << endl;
		outPut << "X = " << conv->BinarytoHex(X) << endl;
		outPut << "L = " << conv->BinarytoHex(L) << endl;
		outPut << "PC = " << conv->BinarytoHex(PC) << endl;
		outPut << "SW = " << conv->BinarytoHex(SW) << endl;
		outPut << "B = " << conv->BinarytoHex(B) << endl;
		outPut << "S = " << conv->BinarytoHex(S) << endl;
		outPut << "T = " << conv->BinarytoHex(T) << endl;
		outPut << "!! Memory" << endl;
		//print 2048 location
		for (int i = 0; i < 2048;i+=8) {
			
			outPut << "0x" << i << ":" << "\t";
			for (int j = 0; j < 8;j++) {
				string datas= mymem->memory1[i + j];
				if (datas != "") {
					outPut << datas << "  ";
				}
				else {
					outPut << "00" << "  ";
				}
				
			}
			outPut << "\n";
		}
		outPut << "!! I/O '05'" << endl;
		outPut << "RENEWABLE ENERGY IS ....." << endl;
		outPut.close();
	}
	else {
		cout << "Error in reading The Output!!";
	}

}
//function to get register in design
string processor::register_design(string bins) {
	if (bins == "0000") {
		return A;
	}
	else if (bins == "0001") {
		return X;
	}
	else if (bins == "0010") {
		return L;
	}
	else if (bins == "0011") {
		return B;
	}
	else if (bins == "0100") {
		return S;
	}
	else if (bins == "0101") {
		return T;
	}
	else if (bins == "0110") {
		return F;
	}
	else if (bins == "1000") {
		return PC;
	}
	else if (bins == "1001") {
		return SW;
	}
	else {
		return "";
	}

}
//function to store any value in register in design
void processor::resgister_set(string value, string bins) {
	if (bins == "0000") {
		A = value;
	}
	else if (bins == "0001") {
		X = value;
	}
	else if (bins == "0010") {
		L = value;
	}
	else if (bins == "0011") {
		B=  value;
	}
	else if (bins == "0100") {
		S = value;
	}
	else if (bins == "0101") {
		T = value;
	}
	else if (bins == "0110") {
		F = value;
	}
	else if (bins == "1000") {
		PC = value;
	}
	else if (bins == "1001") {
		SW = value;
	}
	else {
		std::cout << "register is not found"<<endl;
	}
}
