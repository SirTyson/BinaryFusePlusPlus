all: unit bench

unit : tests/unit.c include/binaryfusefilter.h
	$(CXX) -std=c++17 -O3 -o unit tests/unit.c -lm -Iinclude -Wall -Wextra -Wshadow  -Wcast-qual


ab : tests/a.c tests/b.c
	$(CXX) -std=c++17 -O3 -o c tests/a.c tests/b.c -lm -Iinclude -Wall -Wextra -Wshadow  -Wcast-qual

bench : benchmarks/bench.c include/binaryfusefilter.h
	$(CXX) -std=c++17 -O3 -o bench benchmarks/bench.c -lm -Iinclude -Wall -Wextra -Wshadow  -Wcast-qual

test: unit ab
	./unit

clean:
	rm -f unit bench
