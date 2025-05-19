#include<iostream>
#include"processor.h"
#include"memory.h"
#include"convert.h"
#include<fstream>
#include<string>
#include<cstdlib>
#include<vector>
#include<cmath>
using namespace std;
int main() {
	cout << "This is the SIC/XE simulator using c++ language code           " << endl;
	cout << "This is your input Data" << endl;

	processor* run = new processor();
	run->initialization();
	system("PAUSE");
	return 0;
	
}