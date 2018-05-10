/*  This is a C++ program testing how to pass arrays to functions as pointers  */

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

void ArrayModify1(double Array[]);
void ArrayModify2(double * Array);

int main(){

	double ** MD_Array;
	MD_Array = new double * [2];
	
	for(int k = 0 ; k < 3 ; k++){
		MD_Array[k] = new double [3];
	}

	MD_Array[0][0] = 1;
	MD_Array[0][1] = 0;
	MD_Array[0][2] = 0;
	MD_Array[1][0] = 0;
	MD_Array[1][1] = 1;
	MD_Array[1][2] = 0;

	cout << to_string(MD_Array[0][0]) << '\t' << to_string(MD_Array[0][1]) << '\t' << to_string(MD_Array[0][2]) << "\n";
	cout << to_string(MD_Array[1][0]) << '\t' << to_string(MD_Array[1][1]) << '\t' << to_string(MD_Array[1][2]) << "\n\n";

	double * Array;
	Array = new double [3];

	Array[0] = 1;
	Array[1] = 2;
	Array[2] = 3;

	cout << "Original Array --> \t" << std::to_string(Array[0]) << "\t" << std::to_string(Array[1]) << "\t" << std::to_string(Array[2]);

	cout << "\n\n";
	
	ArrayModify1(Array);

	cout << "ArrayModify1 --> \t" << std::to_string(Array[0]) << "\t" << std::to_string(Array[1]) << "\t" << std::to_string(Array[2]);

	cout << "\n\n";

	ArrayModify2(Array);

	cout << "ArrayModify2 --> \t" << std::to_string(Array[0]) << "\t" << std::to_string(Array[1]) << "\t" << std::to_string(Array[2]);

	cout << "\n\n";

}


void ArrayModify1(double Array[]){

	Array[0] = 2*Array[0];
	Array[1] = 2*Array[1];
	Array[2] = 2*Array[2];

}


void ArrayModify2(double * Array){

	Array[0] = 2*Array[0];
	Array[1] = 2*Array[1];
	Array[2] = 2*Array[2];

}

