CC = g++
CFLAGS = -g -Wall

default: DeepSample

DeepSample: main.o AudioSegmentation.o fastFourierTransform.o
	$(CC) $(CFLAGS) -o DeepSample main.o AudioSegmentation.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

AudioSegmentation.o: AudioSegmentation.cpp AudioSegmentation.h
	$(CC) $(CFLAGS) -c AudioSegmentation.cpp

fastFourierTransform.o: fastFourierTransform.cpp fastFourierTransform.h
	$(CC) $(CFLAGS) -c fastFourierTransform.cpp

clean:
	$(RM) DeepSample *.o *.~ *.out
