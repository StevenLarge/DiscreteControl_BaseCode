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

using namespace std;


int main(){

	//int CPCounterSize = 6; 											// Number of elements in CPVals_Vector and 
	//int TimeCounterSize = 7;										// TotalTime_Vector arrays

	int CPSeed = 5; 												// Initial values of the CPVals_Vector and
	int TimeSeed = 10; 											// TotalTime_Vector arrays

	int CPIncrement = 4; 											// Incrementation of number of CP values

	int * CPVals_Vector; 											// Vector of the various numbers of CP times sampled and
	int * TotalTime_Vector; 										// Different protocol times sampled
	
	CPVals_Vector = new int [CPCounterSize];
	TotalTime_Vector = new int [TimeCounterSize];

	InitializeCPValArray(CPVals_Vector,CPCounterSize,CPSeed,CPIncrement);
	TimeCounterSize = AssignTotalTimeArray(TotalTime_Vector); 				//For now this just directly assigns the time values, there is a intizlize prototype and function in the Numerics.cpp library

	double ** WorkTracker; 													//Declare multidimensional Work tracker array to aggregate result data into a single output file
	WorkTracker = new double * [CPCounterSize];
	for(int index = 0 ; index < TimeCounterSize ; index ++){
		WorkTracker[index] = new double [TimeCounterSize];
	}

	int Realizations = 2000;				//Number of realizations of each nonequilibrium protocol

	double * CPVals; 						//CP Vals and Lag Time arrays that are loaded in from the optimized protocol files
	double * CPTimes;

	double WorkAcc;
	double ProtocolWork;

	double Time; 							//These are the necessary dynamical varibles passed to the Langevin integrator
	double Position;
	double Velocity;

	double * TimePointer = &Time; 			//Pointers to these values are passed to the integrator directly
	double * PositionPointer = &Position;
	double * VelocityPointer = &Velocity;


	for(int ProtocolFlag = 0 ; ProtocolFlag <= 1 ; ProtocolFlag ++){ 					//Loop over protocol classes: Naive, TimeOpt for now

		cout << "\n\nProtocol Flag --> " << std::to_string(ProtocolFlag) << "\n";

		for(int CPCounter = 0 ; CPCounter < CPCounterSize ; CPCounter++){				//Loop over different numbers of CP values

			cout << "\t\t\tNumCPVals --> \t" << std::to_string(CPVals_Vector[CPCounter]) << "\n";

			for(int TimeCounter = 0 ; TimeCounter < TimeCounterSize ; TimeCounter++){	//Loop over different protocol durations considered

				CPVals = new double [CPVals_Vector[CPCounter]];
				CPTimes = new double [CPVals_Vector[CPCounter]];

				ImportProtocol(CPVals, CPTimes, CPVals_Vector[CPCounter], TotalTime_Vector[TimeCounter], ProtocolFlag); 			// '0' Flag imports the Naive protocols, '1' imports optimal protocol

				WorkAcc = 0.0;

				for(int index1 = 0 ; index1 < Realizations ; index1++){ 					//Loop over the number of ralizations of each protocol

					Time = 0;
					Position = CPVals[0];
					Velocity = 0;

					for(int index2 = 0 ; index2 < CPVals_Vector[CPCounter] ; index2++){						//Loop over all CP values within each protocol

						Time = 0; 																			//Need to reset time after each CP change, reported times are lag-times and not absolute times

						while(Time < CPTimes[index2]){ 														//Propogation of dynamics
							LangevinBistable(PositionPointer,VelocityPointer,TimePointer,CPVals[index2]);
						}

						WorkAcc = WorkAcc + CalcWork(Position,CPVals[index2],CPVals[index2+1]);

					}
				}

				ProtocolWork = WorkAcc/((float)(Realizations));

				WorkTracker[CPCounter][TimeCounter] = ProtocolWork;

				WriteSingleWork(ProtocolWork,CPVals_Vector[CPCounter],TotalTime_Vector[TimeCounter],ProtocolFlag);

			}
		}

		WriteWorkArray(WorkTracker,CPVals_Vector,TotalTime_Vector,CPCounterSize,TimeCounterSize,ProtocolFlag);
	
	}
}


