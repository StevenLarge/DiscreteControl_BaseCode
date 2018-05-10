/* This C++ file contains the Protocol read/write routines */

//#include "/Users/stevelarge/Research/DiscreteControl/LinkedCode_CPP/lib/DiscreteControl.h" 			//This is the Discrete control header file, containing function prototypes

#include "include/ReadWrite.h"

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

void ImportProtocol(double * CPVals, double * LagTimes, int NumCPVals, int TotalTime, int FLAG){

	string ImportName;

	if(FLAG == 0){
		//ImportName = "Protocols_Feb12/Naive_CP" + std::to_string(NumCPVals) + "_T" + std::to_string(TotalTime) + ".dat";
		ImportName = "/Users/stevelarge/Research/DiscreteControl/LinkedCode_CPP/NonEquilibrium_Cluster/Protocols/Naive_CP" + std::to_string(NumCPVals) + "_T" + std::to_string(TotalTime) + ".dat";
	}
	else{
		//ImportName = "Protocols_Feb12/TimeOpt_CP" + std::to_string(NumCPVals) + "_T" + std::to_string(TotalTime) + ".dat";
		ImportName = "/Users/stevelarge/Research/DiscreteControl/LinkedCode_CPP/NonEquilibrium_Cluster/Protocols/TimeOpt_CP" + std::to_string(NumCPVals) + "_T" + std::to_string(TotalTime) + ".dat";
	} 

	std::ifstream ReadFile;

	ReadFile.open(ImportName);

	for(int counter = 0 ; counter < NumCPVals ; counter++){
		ReadFile >> CPVals[counter] >> LagTimes[counter];
	}

	ReadFile.close();
	
}

void ImportProtocol_String(double * CPVals, double * LagTimes, int NumCPVals, string ImportName){

	std::ifstream ReadFile;

	ReadFile.open(ImportName);

	for(int counter = 0 ; counter < NumCPVals ; counter ++){
		ReadFile >> CPVals[counter] >> LagTimes[counter];
	}

	ReadFile.close();

}


void WriteSingleWork(double Work, int NumCPVals, int TotalTime, int FLAG){

	string WriteName;

	if(FLAG == 0){
		WriteName = "Work_Feb12/SingleWork/Naive_CP" + std::to_string(NumCPVals) + "_T" + std::to_string(TotalTime) + ".dat";
	}
	else{
		WriteName = "Work_Feb12/SingleWork/TimeOpt_CP" + std::to_string(NumCPVals) + "_T" + std::to_string(TotalTime) + ".dat";
	}

	std::ofstream WriteFile;

	WriteFile.open(WriteName);

	WriteFile << "Work\tCPVals\tTotalTime\n";
	WriteFile << std::to_string(Work) << std::to_string(NumCPVals) << std::to_string(TotalTime);

	WriteFile.close();

}

void WriteWorkArray_Element(double WorkVal, int FLAG){

	string WriteName;

	if(FLAG == 0){
		WriteName = "Work_Feb12/Naive_Total.dat";
	}
	else{
		WriteName = "Work_Feb12/TimeOpt_Total.dat";
	}

	std::ofstream WriteFile;

	WriteFile.open(WriteName, std::ios::app);
	WriteFile << std::to_string(WorkVal) << "\t";
	WriteFile.close();

}

void WriteWorkArray_NewLine(int FLAG){

	string WriteName;

	if(FLAG == 0){
		WriteName = "Work_Feb12/Naive_Total.dat";
	}
	else{
		WriteName = "Work_Feb12/TimeOpt_Total.dat";
	}

	std::ofstream WriteFile;

	WriteFile.open(WriteName, std::ios::app);
	WriteFile << "\n";
	WriteFile.close();

}

void WriteWorkArray_Initial(int * TotalTime_Vector, int TimeCounterSize, int FLAG){

	string WriteName;

	if(FLAG == 0){
		WriteName = "Work_Feb12/Naive_Total.dat";
	}
	else{
		WriteName = "Work_Feb12/TimeOpt_Total.dat";
	}

	std::ofstream WriteFile;

	WriteFile.open(WriteName);
	WriteFile << "\t\t\t";
	
	for(int index = 0 ; index < TimeCounterSize ; index ++){
		WriteFile << std::to_string(TotalTime_Vector[index]) << "\t\t";
	}

	WriteFile << "\n\n";
	WriteFile.close();

}

void WriteWorkArray_CPVal(double CPVal, int FLAG){

	string WriteName;

	if(FLAG == 0){
		WriteName = "Work_Feb12/Naive_Total.dat";
	}
	else{
		WriteName = "Work_Feb12/TimeOpt_Total.dat";
	}

	std::ofstream WriteFile;

	WriteFile.open(WriteName, std::ios::app);
	WriteFile << std::to_string(CPVal) << "\t\t";
	WriteFile.close();

}


void WriteWorkArray(double **WorkArray, int * CPVals, int * TotalTime, int NumCPVals, int NumTimes, int FLAG){

	string WriteName;

	if(FLAG == 0){
		WriteName = "Work_Feb12/Naive_Total_Array.dat";
	}
	else{
		WriteName = "Work_Feb12/TimeOpt_Total_Array.dat";
	}

	std::ofstream WriteFile;

	WriteFile.open(WriteName);

	WriteFile << "\t\t";

	for(int k = 0 ; k < NumTimes ; k++){
		WriteFile << std::to_string(TotalTime[k]) << "\t\t";
	}

	WriteFile << "\n\n";

	for(int index1 = 0 ; index1 < NumCPVals ; index1 ++){
		WriteFile << std::to_string(CPVals[index1]) << "\t\t";

		for(int index2 = 0 ; index2 < NumTimes ; index2 ++){
			WriteFile << std::to_string(WorkArray[index1][index2]) << "\t";
		}

		WriteFile << "\n";

	}
}


