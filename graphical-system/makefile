all:
	g++ *.cpp `pkg-config --cflags gtk+-3.0` -o main `pkg-config --libs gtk+-3.0` -std=c++11 -rdynamic

test:
	g++ *.cpp `pkg-config --cflags gtk+-3.0` -o main `pkg-config --libs gtk+-3.0` -std=c++11 -rdynamic
	./main
	rm main

clean:
	rm main
