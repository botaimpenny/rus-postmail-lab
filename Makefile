all:
	g++ main.cpp pack.cpp -o pack
	./pack
clean:
	rm -f pack
