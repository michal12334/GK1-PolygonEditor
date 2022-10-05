build:
	g++ main.cpp globalModules.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm main

.PHONY:
	clean