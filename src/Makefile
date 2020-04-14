.PHONY:all
all: build

.PHONY:build
build:
	mkdir -p build
	cd build/ && cmake .. && make all --no-print-directory
# pack

.PHONY:clean
clean:
	rm -rf build/
.PHONY: test
test:
	cd build/ && ./calclib_test
# doc
.PHONY:run
run:
	./build/fcalc
.PHONY: clean
profile:
	./build/fcalc_profiling
