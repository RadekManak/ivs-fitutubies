PACK_DIRECTORY=../../Fitutubies-pack
AUTHORS=xgulci00_xmanak20_xmisti00_xzatov00
REPOSITORY_ROOT=..

.PHONY:all
all: build

.PHONY:build
build:
	mkdir -p build
	cd build/ && cmake .. && make all --no-print-directory
pack: doc
	rm -rf ./*build*
	mkdir -p "$(PACK_DIRECTORY)"
	rm -rf "$(PACK_DIRECTORY)"/*

	# Using symlink to get correct directory name in archive
	ln -s $(realpath ..) "$(PACK_DIRECTORY)"/repo
	zip -r "$(PACK_DIRECTORY)"/"$(AUTHORS)".zip doc/
	cd "$(PACK_DIRECTORY)" && zip -r "$(AUTHORS)".zip repo/
	unlink "$(PACK_DIRECTORY)"/repo
.PHONY:clean
clean:
	rm -rf build/
.PHONY: test
test:
	cd build/ && ./calclib_test
.PHONY: doc
doc:
	doxygen Doxyfile
.PHONY:run
run:
	./build/fcalc
.PHONY: clean
profile:
	./build/fcalc_profiling
