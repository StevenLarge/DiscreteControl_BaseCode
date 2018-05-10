/* This is a simple C++ instance of a nonequilibrium protocol propogator for high parallelization */

//Steven Large
//March 6th 2018

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

void LangevinBistable(double * time, double * position, double * velocity, double CPVal);
double CalcWork(double position, double CPInit, double CPFinal);
double ForceParticleBistable(double position, double CP);
double BistableWell(double position, double CP);
string ReadFile(string ReadName, int * NumCPVals);
void ImportProtocol(double * CPVals, double * LagTimes, int NumCPVals, string ImportName);
void WriteWork(double WorkTotal, string WorkWriteName);

std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<> d(0,1);
double GaussRandom;

double DampingVal = 0.25;
double beta = 1.0;
double dt = 0.1;
double mass = 1.0;
double dX = 0.01;

double kL = 12.0;
double kR = 12.0; 				
double DeltaE = 0.0;
double X_m = 1.0;
double BistableTrap = 1.5;


int main(){
	
	int NumCPVals;
	int ProtocolRepetitions = 100000000;

	string ImportName;
	string ReadName;
	ReadName = "ProtocolName.dat";

	string WorkWriteName;
	WorkWriteName = "Work.dat";

	ImportName = ReadFile(ReadName, &NumCPVals);

	cout << "NumCpVals   --> " << std::to_string(NumCPVals) << "\n";
	cout << "Import Name --> " << ImportName << "\n\n";

	double * CPVals;
	double * LagTimes;
	CPVals = new double [NumCPVals];
	LagTimes = new double [NumCPVals];

	ImportProtocol(CPVals, LagTimes, NumCPVals, ImportName);

	double WorkSingle;
	double WorkTotal = 0;

	double position;
	double velocity;
	double time;

	double * timePointer = &time;
	double * positionPointer = &position;
	double * velocityPointer = &velocity;

	for(int k = 0 ; k < ProtocolRepetitions ; k++){

		position = CPVals[0];
		velocity = 0;

		WorkSingle = 0;

		for(int j = 0 ; j < NumCPVals-1 ; j++){

			time = 0;

			while(time < LagTimes[j]){
				LangevinBistable(timePointer,positionPointer,velocityPointer,CPVals[j]);
			}

			WorkSingle += CalcWork(position,CPVals[j],CPVals[j+1]);
		}

		WorkTotal = WorkTotal + WorkSingle;
	}

	WorkTotal = WorkTotal/((float)(ProtocolRepetitions));

	WriteWork(WorkTotal,WorkWriteName);
}



void LangevinBistable(double * time, double * position, double * velocity, double CP){

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

double CalcWork(double position, double CPInit, double CPFinal){

	double Work;
	double EnergyBefore;
	double EnergyAfter;

	EnergyBefore = BistableWell(position,CPInit);
	EnergyAfter = BistableWell(position,CPFinal);

	Work = EnergyAfter - EnergyBefore;

	return Work;
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

double BistableWell(double position, double CP){

	double BistableEnergy;
	double CPEnergy;
	double TotalEnergy;

	BistableEnergy = (-1.0/beta)*log(exp(-0.5*beta*kL*((position + X_m)*(position + X_m))) + exp(-0.5*beta*kR*((position - X_m)*(position - X_m)) - beta*DeltaE));
	CPEnergy = 0.5*BistableTrap*(position - CP)*(position - CP);

	TotalEnergy = BistableEnergy + CPEnergy;

	return TotalEnergy;
}

string ReadFile(string ReadName, int * NumCPVals){
	
	string ImportName;

	std::ifstream ReadFile;

	ReadFile.open(ReadName);

	ReadFile >> ImportName;
	ReadFile >> *NumCPVals;

	ReadFile.close();

	return ImportName;
}

void ImportProtocol(double * CPVals, double * LagTimes, int NumCPVals, string ImportName){

	std::ifstream ReadFile;

	ReadFile.open(ImportName);

	for(int counter = 0 ; counter < NumCPVals ; counter ++){
		ReadFile >> CPVals[counter] >> LagTimes[counter];
	}

	ReadFile.close();
}

void WriteWork(double WorkTotal, string WorkWriteName){

	std::ofstream WriteFile;

	WriteFile.open(WorkWriteName);

	WriteFile << WorkTotal;

	WriteFile.close();
}
