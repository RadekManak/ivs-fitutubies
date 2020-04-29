PACK_DIRECTORY=../../Fitutubies-pack
AUTHORS=xgulci00_xmanak20_xmisti00_xzatov00
REPOSITORY_ROOT=..
VERSION=1.0

.PHONY:all build pack clean test doc run profile

all: build
build:
	mkdir -p build
	cd build/ && cmake .. && make all --no-print-directory
pack: doc install
	rm -rf ./*build*
	mkdir -p "$(PACK_DIRECTORY)"
	rm -rf "$(PACK_DIRECTORY)"/*

	# Using symlink to get correct directory name in archive
	ln -s $(realpath ..) "$(PACK_DIRECTORY)"/repo
	zip -r "$(PACK_DIRECTORY)"/"$(AUTHORS)".zip doc/
	cd ../../install && zip ../Fitutubies-pack/"$(AUTHORS)".zip fitutubiescalculator_"$(VERSION)"_amd64.deb
	cd "$(PACK_DIRECTORY)" && zip -r "$(AUTHORS)".zip repo/
	unlink "$(PACK_DIRECTORY)"/repo
clean:
	rm -rf build/
test:
	cd build/ && ./calclib_test
doc:
	doxygen Doxyfile
run:
	./build/fitutubies-calculator
profile:
	./build/fitutubies-calculator_profiling
install: build
	mkdir -p ../../install
	rm -f ../../install/*
	cd ../  && dpkg-buildpackage -rfakeroot -uc -b
	cd ../../ && mkdir -p install && mv *.* ./install
