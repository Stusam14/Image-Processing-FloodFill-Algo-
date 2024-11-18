findcomp: ConnectedComponent.o PGMimageProcessor.o Driver.o
	g++ ConnectedComponent.o PGMimageProcessor.o Driver.o -o findcomp -std=c++20

ConnectedComponent.o: ConnectedComponent.cpp
	g++ -c ConnectedComponent.cpp -o ConnectedComponent.o

PGMimageProcessor.o: PGMimageProcessor.cpp
	g++ -c PGMimageProcessor.cpp -o PGMimageProcessor.o

Driver.o: Driver.cpp
	g++ -c Driver.cpp -o Driver.o

clean:
	rm *.o findcomp

