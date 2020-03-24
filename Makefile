# Created 2-9-2020
# Author Andrew Moore
# Modified 3-22-2020

CC = g++
CFLAGS = -g -Wall -std=gnu++17
LIBS = -lsndfile -lvorbis -lboost_system -lboost_filesystem
FILES = $(shell git pull)

# Make the DeepSample binary, first making sure the source files aren't stail.
default: 
	$(FILES);\
	make tests;

# Make all the binaries in the project, first making sure the source files aren't stail.
all:   
	$(FILES);\
	make tests;\
	make Samples;

test: 
	$(FILES);\
	make tests;

tests: src/deepSampleTests.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/cepstrum.o src/audioHandler.o src/Utilities.o src/ANN.o src/TestSuite.o
	$(CC) $(CFLAGS) -o DeepSampleTests src/deepSampleTests.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/cepstrum.o src/audioHandler.o src/Utilities.o src/ANN.o src/TestSuite.o $(LIBS)
	$(RM) src/*.o;

clean:
	$(RM) DeepSampleTests SampleGenerator *.o *.~ *.out src/*.o *.txt

# Just make the sample binary, first making sure the source files aren't stail.
Samples: src/sampleGenerator.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/cepstrum.o src/audioHandler.o src/Utilities.o 
	$(CC) $(CFLAGS) -o SampleGenerator src/sampleGenerator.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/cepstrum.o src/audioHandler.o src/Utilities.o $(LIBS)
	$(RM) src/*.o

# Object compilation
deepSampleTests.o: src/deepSampleTests.cpp
	$(CC) $(CFLAGS) -c src/deepSampleTests.cpp $(LIBS)

sampleGenerator.o: src/sampleGenerator.cpp
	$(CC) $(CFLAGS) -c src/sampleGenerator.cpp $(LIBS)

AudioSegmentation.o: src/AudioSegmentation.cpp include/AudioSegmentation.h
	$(CC) $(CFLAGS) -c src/AudioSegmentation.cpp $(LIBS)

FourierTransform.o: src/FourierTransform.cpp include/FourierTransform.h
	$(CC) $(CFLAGS) -c src/FourierTransform.cpp

Utilities.o: src/Utilities.cpp include/Utilities.h
	$(CC) $(CFLAGS) -c src/Utilities.cpp

zeroCrossing.o: src/zeroCrossing.cpp include/zeroCrossing.h
	$(CC) $(CFLAGS) -c src/zeroCrossing.cpp

spectrumFlux.o: src/spectrumFlux.cpp include/spectrumFlux.h
	$(CC) $(CFLAGS) -c src/spectrumFlux.cpp

cepstrum.o: src/cepstrum.cpp include/cepstrum.h
	$(CC) $(CFLAGS) -c src/cepstrum.cpp

ANN.o: src/ANN.cpp include/ANN.h
	$(CC) $(CFLAGS) -c src/ANN.cpp

TestSuite.o: src/TestSuite.cpp include/TestSuite.h
	$(CC) $(CFLAGS) -c src/TestSuite.cpp

