CC := cc
CXX := g++
RUSTC := rustc
CFLAGS := -std=c89 -pedantic -ansi -O3 -march=native -flto
CXXFLAGS := -std=c++17 -O3 -march=native -flto
RUSTFLAGS := -C opt-level=3 -C target-cpu=native -C lto=yes

all: vecbench_c vecbench_cpp vecbench_rust

vecbench_c: vecbench.c ../buf.c
	$(CC) $(CFLAGS) -o vecbench_c vecbench.c -I ../. ../buf.c

vecbench_cpp: vecbench.cpp
	$(CXX) $(CXXFLAGS) -o vecbench_cpp vecbench.cpp

vecbench_rust: vecbench.rs
	$(RUSTC) $(RUSTFLAGS) vecbench.rs -o vecbench_rust

run: vecbench_c vecbench_cpp vecbench_rust
	./vecbench_c
	./vecbench_cpp
	./vecbench_rust

clean:
	rm -f vecbench_c vecbench_cpp vecbench_rust

.PHONY: all clean run
