all: hashTagCounter.cpp FibHeap.cpp Node.cpp
	g++ -static-libstdc++ hashTagCounter.cpp FibHeap.cpp Node.cpp -o hashtagcounter
clean:
	rm -f *.exe
	
	