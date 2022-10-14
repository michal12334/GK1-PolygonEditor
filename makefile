build:
	find -name "*.cpp" -exec g++ -c {} \; -exec echo {} \;
	g++ `find -name "*.o"` -o main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm main *.o

.PHONY:
	clean