VPATH=src:include:include_SP
CC=c++
CXXFLAGS= -I include_SP
CFLAGS= -I include_SP
CPPFLAGS= -I include_SP
mainLib =SpiceNetlistNode.o SpiceNetlistBuilder.o Cstring.o \
         main.o Global_function.o SubcktNode.o functionObject.o \
         arrayOfCstring.o ExtractDeviceList.o GF.o
SpicePaser: $(mainLib)
	$(CC) $^  $(CPPFLAGS) -o ./lab/$@
main.o: main.cc
	$(CC) -c $<
SpiceNetlistNode.o:SpiceNetlistNode.cc 
	$(CC)   -c  $<
SpiceNetlistBuilder.o:SpiceNetlistBuilder.cc 
	$(CC)   -c  $<
SubcktNode.o:SubcktNode.cc 
	$(CC)   -c  $<
arrayOfCstring.o:arrayOfCstring.c 
	$(CC)   -c  $< 
ExtractDeviceList.o:ExtractDeviceList.c
	$(CC)   -c  $< 
Cstring.o:Cstring.c 
	$(CC)   -c  $< 	
functionObject.o:functionObject.cc
	$(CC)   -c  $< 
Global_function.o:Global_function.cc
	$(CC)   -c  $< 
GF.o:GF.c
	$(CC)   -c $<
.PHONY:clean
clean:
	rm -rf *.o SpicePaser 
