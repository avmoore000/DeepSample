# Created 2-9-2020
# Author Andrew Moore
# Modified 2-9-2020

CC = g++
CFLAGS = -g -Wall
LIBS = -lsndfile -logg

default: DeepSample

DeepSample: src/main.o src/AudioSegmentation.o src/FourierTransform.o src/Utilities.o  src/audioHandler.o  
	$(CC) $(CFLAGS) -o DeepSample src/main.o src/AudioSegmentation.o src/FourierTransform.o src/Utilities.o src/audioHandler.o $(LIBS)
	$(RM) src/*.o

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp $(LIBS)

AudioSegmentation.o: src/AudioSegmentation.cpp include/AudioSegmentation.h
	$(CC) $(CFLAGS) -c src/AudioSegmentation.cpp $(LIBS)

FourierTransform.o: src/FourierTransform.cpp include/FourierTransform.h
	$(CC) $(CFLAGS) -c src/FourierTransform.cpp

Utilities.o: src/Utilities.cpp include/Utilities.h
	$(CC) $(CFLAGS) -c src/Utilities.cpp

audioHandler.o: src/audioHandler.cpp include/audioHandler.h
	$(CC) $(CFLAGS) -c src/audioHandler.cpp

clean:
	$(RM) DeepSample *.o *.~ *.out src/*.o
