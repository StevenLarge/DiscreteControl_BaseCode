/* This C++ code contains the trajectory tracking subroutines from the Equilibrium sampling suite */

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

#include "include/DiscreteControl.h"
#include "include/DiscreteControl_Eq.h"

using namespace std;

/* Trajectory tracking routine, this prints a long stationary trajectory to make sure the data looks correct */

void TrajectoryTracker(int SampleLength){

	double CP = -10.0;

	int SampleLength2 = int(SampleLength/dt);

	double * positionArray;
	positionArray = new double [SampleLength2];
	double * timeArray;
	timeArray = new double [SampleLength2];
	double * ForceArray;
	ForceArray = new double [SampleLength2];

	double position = CP;
	double velocity = 0;
	double time = 0;

	double * positionPointer;
	double * velocityPointer;
	double * timePointer;

	positionPointer = &position;
	velocityPointer = &velocity;
	timePointer = &time;

	for(int k = 0 ; k < SampleLength2 ; k++) {
		LangevinBistable(positionPointer,velocityPointer,timePointer,CP);
		positionArray[k] = position;
		timeArray[k] = time;
		ForceArray[k] = ForceParticleBistableTrap(position,CP);
	}

	TrajectoryCorrelation(ForceArray, CP, SampleLength2);

	std:ofstream Writefile;

	Writefile.open("EquilibriumData_Feb21/Trajectory_m10.dat");
	Writefile << "Time\tPosition\n\n";
	for(int k = 0 ; k < SampleLength2 ; k++) {
		Writefile << timeArray[k] << "\t" << positionArray[k] << "\n";
	}
	Writefile.close();

	Writefile.open("EquilibriumData_Feb21/TrajectoryForce_m10.dat");
	Writefile << "Time\tForce\n\n";
	for(int k = 0 ; k < SampleLength2 ; k++) {
		Writefile << timeArray[k] << "\t" << ForceArray[k] << "\n";
	}
	Writefile.close();


	CP = 0.0;

	position = CP;
	velocity = 0;
	time = 0;

	for(int k = 0 ; k < SampleLength2 ; k++) {
		LangevinBistable(positionPointer,velocityPointer,timePointer,CP);
		positionArray[k] = position;
		timeArray[k] = time;
		ForceArray[k] = ForceParticleBistableTrap(position,CP);
	}

	TrajectoryCorrelation(ForceArray, CP, SampleLength2);

	Writefile.open("EquilibriumData_Feb21/Trajectory_0.dat");
	Writefile << "Time\tPosition\n\n";
	for(int k = 0 ; k < SampleLength2 ; k++) {
		Writefile << timeArray[k] << "\t" << positionArray[k] << "\n";
	}
	Writefile.close();

	Writefile.open("EquilibriumData_Feb21/TrajectoryForce_0.dat");
	Writefile << "Time\tForce\n\n";
	for(int k = 0 ; k < SampleLength2 ; k++) {
		Writefile << timeArray[k] << "\t" << ForceArray[k] << "\n";
	}
	Writefile.close();

}


void TrajectoryCorrelation(double * ForceArray, double CP, int SampleTime) {

	int CorrLagMAX = int(500/dt);

	double * LagTime;
	LagTime = new double [CorrLagMAX];

	double * Correlation;
	Correlation = new double [CorrLagMAX];

	double TimeCounter = 0.0;

	for(int k = 0 ; k < CorrLagMAX ; k++) {
		Correlation[k] = 0.0;
		LagTime[k] = TimeCounter;
		TimeCounter += dt;
	}

	for(int k = 0 ; k < SampleTime-CorrLagMAX ; k++) {
		for(int i = 0 ; i < CorrLagMAX ; i++) {
			Correlation[i] += ForceArray[k]*ForceArray[k+i];
		}
	}

	for(int k = 0 ; k < CorrLagMAX ; k++) {
		Correlation[k] = Correlation[k]/double(SampleTime-CorrLagMAX);
	}

	std:ofstream Writefile;

	Writefile.open("EquilibriumData_Feb21/ForceCorrelation_" + std::to_string(int(CP)) + ".dat");
	Writefile << "LagTime" << "\t" << "Correlation" << "\n\n";
	for(int k = 0 ; k < CorrLagMAX ; k++) {
		Writefile << LagTime[k] << "\t" << Correlation[k] << "\n";
	}
	Writefile.close();

}





