/* This C++ file contains the some of the random numerical routines needed for Discrete control simulations */

#include "include/Numerics.h"

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

void InitializeCPValArray(int * CPVals_Vector, int CPCounterSize, int CPSeed, int CPIncrement){

	int CP = CPSeed;

	for(int k = 0 ; k < CPCounterSize ; k ++){
		CPVals_Vector[k] = CP;
		CP += CPIncrement;
	}
}


int AssignTotalTimeArray(int * TotalTime_Vector){

	int TimeCounterSize = 7; 							//Return the number of elements of the array

	TotalTime_Vector[0] = 1;
	TotalTime_Vector[1] = 5;
	TotalTime_Vector[2] = 10;
	TotalTime_Vector[3] = 50;
	TotalTime_Vector[4] = 100;
	TotalTime_Vector[5] = 500;
	TotalTime_Vector[6] = 1000;

	return TimeCounterSize;
}

void InitializeTotalTimeArray(int * TotalTime_Vector, int TimeCounterSize, int TimeSeed, int LogTimeIncrement){

	int TotalTime = TimeSeed;

	for(int k = 0 ; k < TimeCounterSize ; k ++){
		TotalTime_Vector[k] = TotalTime;
		TotalTime = TotalTime*LogTimeIncrement;
	}
}

