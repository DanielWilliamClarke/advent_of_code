# Tasks
install:
	mkdir -p dist/$(configuration); \
	cd dist/$(configuration); \
	conan install ../../conanfile.txt --output-folder . --build=missing --profile ../../profile.txt -s build_type=$(configuration); \
	cd ../..
build:
	cd dist/$(configuration); \
	cmake -DCMAKE_BUILD_TYPE=$(configuration) ../..; \
    make; \
	cd ../..
runtests: 
	make build; \
	./dist/$(configuration)/test/AOC_2023_test
run: 
	./dist/$(configuration)/src/AOC_2023

# Debug 
install_debug: 
	make install configuration=Debug
build_debug: 
	make build configuration=Debug
run_debug:
	make run configuration=Debug
runtests_debug:
	make runtests configuration=Debug

debug: install_debug build_debug run_debug

# Release
install_release: 
	make install configuration=Release
build_release: 
	make build configuration=Release
run_release: 
	make run configuration=Release

release: install_release build_release run_release