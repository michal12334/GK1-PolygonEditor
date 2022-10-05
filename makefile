build:
	g++ `find -name "*.cpp"` -o main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm main

.PHONY:
	clean