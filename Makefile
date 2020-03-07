all: build
	cd build/ && cmake .. && make all --no-print-directory

build:
	mkdir build

# pack

clean:
	rm -r build/

test:
	cd build/ && ctest -C Debug
# doc
run:
	./build/fcalc

profile:
	./build/fcalc_profiling
