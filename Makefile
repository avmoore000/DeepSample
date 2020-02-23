# Created 2-9-2020
# Author Andrew Moore
# Modified 2-9-2020

CC = g++
CFLAGS = -g -Wall

default: DeepSample

DeepSample: src/main.o src/AudioSegmentation.o src/FourierTransform.o src/Utilities.o
	$(CC) $(CFLAGS) -o DeepSample src/main.o src/AudioSegmentation.o src/FourierTransform.o src/Utilities.o
	$(RM) src/*.o

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

AudioSegmentation.o: src/AudioSegmentation.cpp include/AudioSegmentation.h
	$(CC) $(CFLAGS) -c src/AudioSegmentation.cpp

FourierTransform.o: src/FourierTransform.cpp include/FourierTransform.h
	$(CC) $(CFLAGS) -c src/FourierTransform.cpp

Utilities.o: src/Utilities.cpp include/Utilities.h
	$(CC) $(CFLAGS) -c src/Utilities.cpp

clean:
	$(RM) DeepSample *.o *.~ *.out src/*.o
