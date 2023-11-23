
all: install build run

install:
	cd dist/Debug && conan install ../../conanfile.txt --output-folder . --build=missing --profile ../../profile.txt -s build_type=Debug && cd ../..

build:
	cd dist/Debug && cmake ../.. && make && cd ../..

runtests: 
	make build && ./dist/Debug/test/AOC_2023_test

run: 
	./dist/Debug/src/AOC_2023

