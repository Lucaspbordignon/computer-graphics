CC := g++
HEADERS := -I include
SOURCE= main.cpp src/*.cpp

all:
	$(CC) $(SOURCE) `pkg-config --cflags gtk+-3.0` -o main `pkg-config --libs gtk+-3.0` $(HEADERS) -std=c++11 -rdynamic

test:
	$(CC) $(SOURCE) `pkg-config --cflags gtk+-3.0` -o main `pkg-config --libs gtk+-3.0` $(HEADERS) -std=c++11 -rdynamic
	./main
	rm main

clean:
	rm main
