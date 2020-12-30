## use "icc" to compile source files.
##CC = icc
CC = gcc
## Use the Intel Linker
##LD = icpc
LD = g++

LAPTOP = 1

#INCLUDE_PATH=/opt/intel/mkl/8.0.1/include

#INCLUDE_PATH_VECLIB=/System/Library/Frameworks/vecLib.framework/Versions/A/Headers

#LIB_PATH=/opt/intel/mkl/8.0.1/lib/32

## ifdef WORK
#LIB_PATH=/opt/intel/mkl/8.0.1/lib/em64t/
# LIB_PATH = .
## endif

## Compiler flags go here.
CFLAGS = -O2 -c 
##CFLAGS = -g -c
## Linker flags go here. 
##-L$(LIB_PATH)

## use this command to erase files.
RM = /bin/rm -f

## list of generated object files.

DPMATCHSRVFAPP_OBJS = dpmatchsrvfapp.o dpmatch.o

## program executable file name.


DPMATCHSRVFAPP = dpmatchsrvfapp

src_dir = ../src/dpmatchsrvf/
bin_dir = ./bin/

## top-level rule, to compile everything.
all:	$(DPMATCHSRVFAPP)

## rule to link the program

$(DPMATCHSRVFAPP):$(DPMATCHSRVFAPP_OBJS)
	$(LD) $(DPMATCHSRVFAPP_OBJS) $(LDFLAGS) -o $(DPMATCHSRVFAPP)


dpmatch.o: $(src_dir)dpmatch.cpp $(src_dir)dpmatch.h
	$(CC) $(CFLAGS) $(src_dir)dpmatch.cpp

dpmatchsrvfapp.o: $(src_dir)dpmatchsrvfapp.cpp
	$(CC) $(CFLAGS) $(src_dir)dpmatchsrvfapp.cpp	

	
# DP_Shape_Match.o: $(src_dir)DP_Shape_Match.cpp
# 	$(CC) $(CFLAGS) $(src_dir)DP_Shape_Match.cpp	

## rule for cleaning re-compilable files.
clean:
	$(RM) $(DPMATCHSRVFAPP) $(DPMATCHSRVFAPP_OBJS)	
