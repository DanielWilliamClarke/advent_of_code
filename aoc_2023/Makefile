# Tasks
build:
	mkdir -p dist/$(configuration); \
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
build_debug: 
	make build configuration=Debug
run_debug:
	make run configuration=Debug
runtests_debug:
	make runtests configuration=Debug

debug: build_debug run_debug

# Release
build_release: 
	make build configuration=Release
run_release: 
	make run configuration=Release

release: build_release run_release