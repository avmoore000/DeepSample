# Created 2-9-2020
# Author Andrew Moore
# Modified 3-8-2020

CC = g++
CFLAGS = -g -Wall
LIBS = -lsndfile -lvorbis

default: DeepSample

DeepSample: src/main.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/cepstrum.o src/audioHandler.o src/Utilities.o src/ANN.o src/TestSuite.o 
	$(CC) $(CFLAGS) -o DeepSample src/main.o src/FourierTransform.o src/zeroCrossing.o src/spectrumFlux.o src/cepstrum.o src/audioHandler.o src/Utilities.o src/ANN.o src/TestSuite.o $(LIBS)
	$(RM) src/*.o

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp $(LIBS)

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

clean:
	$(RM) DeepSample *.o *.~ *.out src/*.o *.txt
