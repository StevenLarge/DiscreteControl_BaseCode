/* This is a C++ implementation of a dynamical nonequilibrium propogator for calculating the work required to execute a discrete protocol */

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

#include "include/DiscreteControl.h"
#include "include/ReadWrite.h"
#include "include/Numerics.h"

void InitializeCPValVector(int * CPValVector);
void InitializeTotalTimeVector(int * TotalTimeVector);

using namespace std;


int main(){

	string ReadPath = "NonEquilibrium_Cluster/Protocols/";
	string WritePath = "NonEquilibrium_Cluster/Work/";

	int Protocol_Repetitions = 100000;

	string ReadName_Time;
	//string ReadName_Space;
	//string ReadName_Full;
	string ReadName_Naive;

	int NumCPVals = 10;
	int NumLagTimes = 6;

	int * CPValVector;
	int * TotalTimeVector;
	CPValVector = new int [NumCPVals];
	TotalTimeVector = new int [NumLagTimes];

	InitializeCPValVector(CPValVector);
	InitializeTotalTimeVector(TotalTimeVector);

	for(int k = 0 ; k < NumCPVals ; k++){

		for(int j = 0 ; j < NumLagTimes ; j++){

			double * CPVals_Time;
			double * LagTimes_Time;
			//double * CPVals_Space;
			//double * LagTimes_Space;
			//double * CPVals_Full;
			//double * LagTimes_Full;
			double * CPVals_Naive;
			double * LagTimes_Naive;

			CPVals_Time = new double [CPValVector[k]];
			LagTimes_Time = new double [CPValVector[k]];
			//CPVals_Space = new double [CPValVector[k]];
			//LagTimes_Space = new double [CPValVector[k]];
			//CPVals_Full = new double [CPValVector[k]];
			//LagTimes_Full = new double [CPValVector[k]];
			CPVals_Naive = new double [CPValVector[k]];
			LagTimes_Naive = new double [CPValVector[k]];
			
			double * WorkArray_Time;
			//double * WorkArray_Space;
			//double * WorkArray_Full;
			double * WorkArray_Naive;

			WorkArray_Time = new double [Protocol_Repetitions];
			//WorkArray_Space = new double [Protocol_Repetitions];
			//WorkArray_Full = new double [Protocol_Repetitions];
			WorkArray_Naive = new double [Protocol_Repetitions];

			ReadName_Time = ReadPath + "TimeOpt_CP" + std::to_string(CPValVector[k]) + "_T" + std::to_string(TotalTimeVector[j]) + ".dat"; 
			//ReadName_Space = ReadPath + "SpaceOpt_CP" + std::to_string(CPValVector[k]) + "_T" + std::to_string(TotalTimeVector[j]) + ".dat";
			//ReadName_Full = ReadPath + "FullOpt_CP" + std::to_string(CPValVector[k]) + "_T" + std::to_string(TotalTimeVector[j]) + ".dat";
			ReadName_Naive = ReadPath + "Naive_CP" + std::to_string(CPValVector[k]) + "_T" + std::to_string(TotalTimeVector[j]) + ".dat";

			ImportProtocol_String(CPVals_Time,LagTimes_Time,CPValVector[k],ReadName_Time);
			//ImportProtocol_String(CPVals_Space,LagTimes_Space,CPValVector[k],ReadName_Space);
			//ImportProtocol_String(CPVals_Full,LagTimes_Full,CPValVector[k],ReadName_Full);
			ImportProtocol_String(CPVals_Naive,LagTimes_Naive,CPValVector[k],ReadName_Naive);

			PropogateProtocol(WorkArray_Time,CPVals_Time,LagTimes_Time,CPValVector[k],Protocol_Repetitions);
			//WorkArray_Space = PropogateProtocol(CPVals_Space,LagTimes_Space,Protocol_Repetitions);
			//WorkArray_Full = PropogateProtocol(CPVals_Full,LagTimes_Full,Protocol_Repetitions);
			PropogateProtocol(WorkArray_Naive,CPVals_Naive,LagTimes_Naive,CPValVector[k],Protocol_Repetitions);

			//WriteWorkArray(WorkArray_Time);
			//WriteWorkArray(WorkArray_Naive);

			double WorkAcc_Time = 0;
			double WorkAcc_Naive = 0;

			for(int BLAH = 0 ; BLAH < Protocol_Repetitions ; BLAH++){
				WorkAcc_Naive += WorkArray_Naive[BLAH];
				WorkAcc_Time += WorkArray_Time[BLAH];
			}

			double AvgWork_Time = WorkAcc_Time/((float)(Protocol_Repetitions));
			double AvgWork_Naive = WorkAcc_Naive/((float)(Protocol_Repetitions));

			cout << "AverageWork_Time -->  " << std::to_string(AvgWork_Time) << "\n\n";
			cout << "AverageWork_Naive --> " << std::to_string(AvgWork_Naive) << "\n\n";

			delete WorkArray_Time;
			delete WorkArray_Naive;
			delete CPVals_Time;
			delete CPVals_Naive;
			delete LagTimes_Time;
			delete LagTimes_Naive;

			break;

		}

		break;
	}

}

void InitializeCPValVector(int * CPValVector){

	CPValVector[0] = 15;
	CPValVector[1] = 7;
	CPValVector[2] = 9;	
	CPValVector[3] = 11;	
	CPValVector[4] = 13;	
	CPValVector[5] = 15;	
	CPValVector[6] = 17;	
	CPValVector[7] = 19;	
	CPValVector[8] = 21;
	CPValVector[9] = 25;	
	
}

void InitializeTotalTimeVector(int * TotalTimeVector){

	TotalTimeVector[0] = 100;
	TotalTimeVector[1] = 5;
	TotalTimeVector[2] = 10;
	TotalTimeVector[3] = 50;
	TotalTimeVector[4] = 100;
	TotalTimeVector[5] = 500;

}

