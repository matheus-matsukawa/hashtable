example: example.c hashtable.c
	clear
	gcc example.c hashtable.c -o example
	./example
	rm -f example

benchmark: benchmark.c hashtable.c
	clear
	gcc benchmark.c hashtable.c -o benchmark
	./benchmark
	rm -f benchmark
	