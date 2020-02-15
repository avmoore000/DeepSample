CC = g++
CFLAGS = -g -Wall

default: DeepSample

DeepSample: main.o AudioSegmentation.o FourierTransform.o
	$(CC) $(CFLAGS) -o DeepSample main.o AudioSegmentation.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

AudioSegmentation.o: AudioSegmentation.cpp AudioSegmentation.h
	$(CC) $(CFLAGS) -c AudioSegmentation.cpp

fastFourierTransform.o: FourierTransform.cpp FourierTransform.h
	$(CC) $(CFLAGS) -c FourierTransform.cpp

clean:
	$(RM) DeepSample *.o *.~ *.out
