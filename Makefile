#MAKEFILE for Propogator routine
#
#Steven Large
#January 14th 2018

PRODUCT_NEQ = NoneqPropogator.exe
PRODUCT_EQ = EquilibriumSampling.exe

ODIR = obj
LDIR = lib
IDIR = include
SDIR = src

MAINFILE_NEQ = $(SDIR)/Nonequilibrium_Protocol.cpp
MAINFILE_EQ = $(SDIR)/EquilibriumSampling.cpp

SOURCES_NEQ = $(SDIR)/Propogator.cpp
LIBRARIES_NEQ = $(LDIR)/ReadWrite.cpp
LIBRARIES_NEQ_2 = $(LDIR)/Numerics.cpp
OBJECTS_NEQ = $(SDIR)/$(ODIR)/Propogator.o
OBJECTS_NEQ_LIB = $(SDIR)/$(ODIR)/ReadWrite.o
OBJECTS_NEQ_LIB_2 = $(SDIR)/$(ODIR)/Numerics.o

SOURCES_EQ = $(SDIR)/Propogator.cpp
LIBRARIES_EQ = $(LDIR)/TrajectoryTracking.cpp
OBJECTS_EQ = $(SDIR)/$(ODIR)/Propogator.o
OBJECTS_EQ_LIB = $(SDIR)/$(ODIR)/TrajectoryTracking.o

CFLAGS = -I.

DEPS_NEQ = $(IDIR)/DiscreteControl.h $(IDIR)/ReadWrite.h $(IDIR)/Numerics.h
DEPS_EQ = $(IDIR)/DiscreteControl.h $(IDIR)/DiscreteControl_Eq.h

CC = g++ -std=c++11 -O3
#CC = g++ -O3

all: $(PRODUCT_NEQ) $(PRODUCT_EQ)

$(OBJECTS_NEQ): $(SOURCES_NEQ)
	$(CC) -c $(SOURCES_NEQ) -o $(OBJECTS_NEQ) $(CFLAGS)

$(OBJECTS_NEQ_LIB): $(LIBRARIES_NEQ)
	$(CC) -c $(LIBRARIES_NEQ) -o $(OBJECTS_NEQ_LIB) $(CFLAGS) 

$(OBJECTS_NEQ_LIB_2): $(LIBRARIES_NEQ_2)
	$(CC) -c $(LIBRARIES_NEQ_2) -o $(OBJECTS_NEQ_LIB_2) $(CFLAGS)

#$(OBJECTS_EQ): $(SOURCES_EQ)
#	$(CC) -c $(SOURCES_EQ) -o $(OBJECTS_EQ) $(CFLAGS)

$(OBJECTS_EQ_LIB): $(LIBRARIES_EQ)
	$(CC) -c $(LIBRARIES_EQ) -o $(OBJECTS_EQ_LIB) $(CFLAGS)

$(PRODUCT_NEQ): $(MAINFILE_NEQ) $(OBJECTS_NEQ) $(OBJECTS_NEQ_LIB) $(OBJECTS_NEQ_LIB_2) $(DEPS_NEQ)
	$(CC) $(MAINFILE_NEQ) $(OBJECTS_NEQ) $(OBJECTS_NEQ_LIB) $(OBJECTS_NEQ_LIB_2) -o $(PRODUCT_NEQ) $(CFLAGS)

$(PRODUCT_EQ): $(MAINFILE_EQ) $(OBJECTS_EQ) $(OBJECTS_EQ_LIB) $(DEPS_EQ)
	$(CC) $(MAINFILE_EQ) $(OBJECTS_EQ) $(OBJECTS_EQ_LIB) -o $(PRODUCT_EQ) $(CFLAGS)



clean:
	rm -f $(SDIR)/$(ODIR)/*.o


clean_ex:
	rm *.exe

