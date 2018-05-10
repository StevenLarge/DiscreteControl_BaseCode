/* This is a header file for the Discrete Control Nonequilbrium simulations */


/* Global variable declarations */

extern double dt;
extern double CPMax;
extern double CP;
extern int MAXLAG;
extern double EqTime;
extern int TotalStats;
extern double dX;


/* Propogator routines */

void HelloWorld(int a);

void LangevinBistable(double * position, double * velocity, double * time, double CP);
void Langevin(double * position, double * velocity, double * time, double CP);

double ForceParticleTrap(double position, double CP);
double ForceParticleBistable(double position, double CP);
double ForceParticleBistableTrap(double position, double CP);
double BistableWell(double position, double CP);
double CalcWork(double position, double CPInit, double CPFinal);

void PropogateProtocol(double * WorkArray, double * CPVals, double * LagTimes, int NumCPVals, int ProtocolRepetitions);

/* Numerics Routines */

//int ArraySize(int * Array);
