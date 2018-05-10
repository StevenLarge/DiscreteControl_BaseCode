/* This is a C++ implementation of a dynamical nonequilibrium propogator for calculating the work required to execute a discrete protocol */

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

//#include "/Users/stevelarge/Research/DiscreteControl/LinkedCode_CPP/lib/DiscreteControl.h"

#include "include/DiscreteControl.h"
#include "include/ReadWrite.h"

using namespace std;


int main(){

	double * CPVals_Vector;
	double * TotalTime_Vector;
	CPVals_Vector = new double [7,9,11,13];
	TotalTime_Vector = new double [100,1000,10000];

	//for(int k = 0 ; k < CPVals_Vector.size() ; k++){

		double * CPVals;
		double * CPTimes;
		CPVals = new double [CPVals_Vector[k]];
		CPTimes = new double [CPVals_Vector[k]];

		ImportName = "Protocols/Naive_CP9_T500.dat";

		ImportProtocol(CPVals, CPTimes, ImportName);

	cout << "CPVals\tCPTimes:\n";
	for(int k = 0 ; k < 9 ; k++);
		cout << CPVals[k] << "\t" << CPTimes[k] 

	//}


}


