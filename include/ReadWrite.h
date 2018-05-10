/* This is a header file for the Discrete Control Nonequilbrium simulations pertaining to protocol read-in */

#include <string>

void ImportProtocol(double * CPVals, double * LagTimes, int NumCPVals, int TotalTime, int FLAG=0);
void ImportProtocol_String(double * CPVals, double * LagTimes, int NumCPVals, std::string FileName);
void WriteSingleWork(double ProtocolWork, int NumCPVals, int TotalTime, int FLAG);
void WriteWorkArray(double **WorkArray, int * CPVals, int * TotalTime, int NumCPVals, int NumTimes, int FLAG);
void WriteWorkArray_NewLine(int FLAG);
void WriteWorkArray_Element(double Work, int FLAG);
void WriteWorkArray_CPVal(double CPVal, int FLAG);
void WriteWorkArray_Initial(int * TotalTime_Vector, int TimeCounterSize, int FLAG);

