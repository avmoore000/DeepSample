# Created 2-9-2020
# Author Andrew Moore
# Modified 3-22-2020

CC = g++
CFLAGS = -g -Wall -std=gnu++17
LIBS = -lsndfile -lvorbis -lboost_system -lboost_filesystem
DIR = $(shell mkdir build)
CLEANDIR = $(shell rm -rf build)
FILES = $(shell git pull)

# Make the DeepSample binary, first making sure the source files aren't stail.
default: 
#	$(FILES);
	$(DIR)\
	make test;\
	make sample;\
	make anni;\

# Make all the binaries in the project, first making sure the source files aren't stail.
all:   
	#$(FILES);
	$(DIR)\
	make test;\
	make sample;\
	make anni;\

# Make the DeepSampleTest binary
test: 
#	$(FILES);
	$(DIR)\
	make tests;

# Make the SampleGenerator binary

sample: 
#	$(FILES);
	$(DIR)
	make Samples;\
	make driver;

# Make the ANNI binary
anni:
#	$(FILES);
	$(DIR)\
	make DeepSample;

# Just make the test binary
tests: src/deepSampleTests.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/spectrumCentroid.o src/cepstrum.o src/audioHandler.o src/Utilities.o src/ANN.o src/TestSuite.o src/AudioWave.o
	$(CC) $(CFLAGS) -o build/DeepSampleTests src/deepSampleTests.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/spectrumCentroid.o src/cepstrum.o src/audioHandler.o src/Utilities.o src/ANN.o src/TestSuite.o src/AudioWave.o $(LIBS)
	$(RM) src/*.o;

# Just make the sample binary, first making sure the source files aren't stail.
Samples: src/sampleGenerator.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/spectrumCentroid.o src/cepstrum.o src/audioHandler.o src/Utilities.o src/AudioWave.o 
	$(CC) $(CFLAGS) -o build/SampleGenerator src/sampleGenerator.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/spectrumCentroid.o src/cepstrum.o src/audioHandler.o src/Utilities.o src/AudioWave.o $(LIBS)
	$(RM) src/*.o

# Make driver binary
driver: src/driver.o 
	$(CC) $(CFLAGS) -o build/genSamples src/driver.o $(LIBS)

# Make ANNI binary
DeepSample: src/anniDriver.o src/ANN.o src/AudioWave.o src/Utilities.o 
	$(CC) $(CFLAGS) -o build/DeepSample src/anniDriver.o src/ANN.o src/AudioWave.o src/Utilities.o $(LIBS)
	$(RM) src/*.o

# Clean up the directory
clean:
	$(CLEANDIR)
	$(RM) *.o *.~ *.out src/*.o *.txt;\

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

spectrumCentroid.o: src/sprectrumCentroid.cpp include/spectrumCentroid.h
	$(CC) $(CFLAGS) -c src/spectrumCentroid.cpp

cepstrum.o: src/cepstrum.cpp include/cepstrum.h
	$(CC) $(CFLAGS) -c src/cepstrum.cpp

ANN.o: src/ANN.cpp include/ANN.h
	$(CC) $(CFLAGS) -c src/ANN.cpp

anniDriver.o: src/anniDriver.cpp
	$(CC) $(CFLAGS) -c src/anniDriver.cpp

driver.o: src/driver.cpp
	$(CC) $(CFLAGS) -c src/driver.cpp

TestSuite.o: src/TestSuite.cpp include/TestSuite.h
	$(CC) $(CFLAGS) -c src/TestSuite.cpp

AudioWave.o: src/AudioWave.cpp include/AudioWave.h
	$(CC) $(CFLAGS) -c src/AudioWave.cpp
