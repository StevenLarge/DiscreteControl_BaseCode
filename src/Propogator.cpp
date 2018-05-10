/* This C++ file contains the Dynamical propogator files */

//#include "/Users/stevelarge/Research/DiscreteControl/LinkedCode_CPP/lib/DiscreteControl.h" 			//This is the Discrete control header file, containing function prototypes

#include "include/DiscreteControl.h"

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;


/* Global declaration of random device */

std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<> d(0,1);
double GaussRandom;


/* Global variable declarations for Langevin integrator parameters */

double TrapStrength = 1.0;
double DampingVal = 0.25;
double beta = 1.0;
double dt = 0.1;
double mass = 1.0;


/* Global variables for Bistable well parameters */

double kL = 12.0;				//Also good value for Trap = 1.5
double kR = 12.0; 				
//double kL = 10.50; 			//Good Value with Trap = 1.5
//double kR = 10.50;
//double kL = 0.02636;
//double kR = 0.02636;
//double kL = 0.2;
//double kR = 0.2;
//double kL = 0.11386;
//double kR = 0.11386;
//double kL = 0.06386; 
//double kR = 0.06386;
//double kL = 0.0388;
//double kR = 0.0388;
//double kL = 0.02636;
//double kR = 0.02636;
double DeltaE = 0.0;
//double X_m = 5.0;
//double X_m = 10.0;
double X_m = 1.0;
double BistableTrap = 1.5;
//double BistableTrap = 0.006077;
//double BistableTrap = 0.048614;

/* Global variables for simulation parameters */

//double EqTime = 500;
//double CPMin = -1.0; 					//New values, used to be \pm 1
//double CPMax = 1.0;
//double dX = 0.1;
double dX = 0.05;
//int HUN_MILLION = 100000000;
//int TEN_MILLION = 10000000;
//int ONE_MILLION = 1000000;


void HelloWorld(int a){

	cout << "\n\n----- Hollow World! ----- \n\n";

}


/* Langevin Integrators */

void LangevinBistable(double * position, double * velocity, double * time, double CP){

	//cout << "\tCP --> " << std::to_string(CP) << "\n";

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleBistable(*position,CP)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleBistable(*position,CP)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
}


void Langevin(double * position, double * velocity, double *time, double CP){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleTrap(*position,CP)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleTrap(*position,CP)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	
}


/* Auxillary Numerical Routines */

double ForceParticleTrap(double position, double CP){

	double Force = -TrapStrength*(position - CP);
	return Force;
}

double ForceParticleBistable(double position, double CP){

	double EnergyLeft;
	double EnergyRight;
	double ForceBistable;

	EnergyLeft = BistableWell(position - dX, CP);
	EnergyRight = BistableWell(position + dX, CP);

	ForceBistable = -1.0*(EnergyRight - EnergyLeft)/(2*dX);

	return ForceBistable;
}

double ForceParticleBistableTrap(double position, double CP) {

	//cout << "\t\tposition --> " << std::to_string(position) << "\n";
	//cout << "\t\tCP       --> " << std::to_string(CP) << "\n";

	double Force = -BistableTrap*(position - CP);
	return Force;
}

double BistableWell(double position, double CP){

	double BistableEnergy;
	double CPEnergy;
	double TotalEnergy;

	BistableEnergy = (-1.0/beta)*log(exp(-0.5*beta*kL*((position + X_m)*(position + X_m))) + exp(-0.5*beta*kR*((position - X_m)*(position - X_m)) - beta*DeltaE));
	CPEnergy = 0.5*BistableTrap*(position - CP)*(position - CP);

	TotalEnergy = BistableEnergy + CPEnergy;

	return TotalEnergy;
}

double CalcWork(double position, double CPInit, double CPFinal){

	double Work;
	double EnergyBefore;
	double EnergyAfter;

	EnergyBefore = BistableWell(position,CPInit);
	EnergyAfter = BistableWell(position,CPFinal);

	Work = EnergyAfter - EnergyBefore;

	return Work;
}


void PropogateProtocol(double * WorkArray, double * CPVals, double * LagTimes, int NumCPVals, int ProtocolRepetitions){

	double WorkAcc;

	double position;
	double velocity;
	double time;

	double * timePointer = &time;
	double * positionPointer = &position;
	double * velocityPointer = &velocity;


	for(int j = 0 ; j < ProtocolRepetitions ; j++){

		time = 0;
		position = CPVals[0];
		velocity = 0;

		WorkAcc = 0;

		for(int k = 0 ; k < NumCPVals-1 ; k++){

			time = 0;

			while(time < LagTimes[k]){
				LangevinBistable(positionPointer,velocityPointer,timePointer,CPVals[k]);
			}

			WorkAcc = WorkAcc + CalcWork(position,CPVals[k],CPVals[k+1]);

		}

		WorkArray[j] = WorkAcc;
	}

}