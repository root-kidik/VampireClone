CMAKE_COMMON_FLAGS ?= -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
CMAKE_DEBUG_FLAGS ?= 
CMAKE_RELEASE_FLAGS ?=
CMAKE_OS_FLAGS ?= 
NPROCS ?= $(shell nproc)
CLANG_FORMAT ?= clang-format

CMAKE_DEBUG_FLAGS += -DCMAKE_BUILD_TYPE=Debug $(CMAKE_COMMON_FLAGS)
CMAKE_RELEASE_FLAGS += -DCMAKE_BUILD_TYPE=Release $(CMAKE_COMMON_FLAGS)

# Run cmake
.PHONY: cmake-debug
cmake-debug:
	cmake -B build_debug $(CMAKE_DEBUG_FLAGS)
	rm -rf compile_commands.json
	ln -s build_debug/compile_commands.json compile_commands.json

.PHONY: cmake-release
cmake-release:
	cmake -B build_release $(CMAKE_RELEASE_FLAGS)
	rm -rf compile_commands.json
	ln -s build_release/compile_commands.json compile_commands.json

build_debug/CMakeCache.txt: cmake-debug
build_release/CMakeCache.txt: cmake-release

# Build using cmake
.PHONY: build-debug build-release
build-debug build-release: build-%: build_%/CMakeCache.txt
	cmake --build build_$* -j $(NPROCS) --target  VampireSurvivors

# Start the service (via testsuite service runner)
.PHONY: start-debug start-release
start-debug start-release: start-%: build-%
	@cd ./build_$* && ./bin/VampireSurvivors 

# Cleanup data
.PHONY: clean-debug clean-release
clean-debug clean-release: clean-%:
	cd build_$* && $(MAKE) clean

.PHONY: dist-clean
dist-clean:
	@rm -rf build_*

# Install
.PHONY: install-debug install-release
install-debug install-release: install-%: build-%
	@cd build_$* && \
		cmake --install . -v 

.PHONY: install
install: install-release

# Format the sources
.PHONY: format
format:
	@find src -name '*pp' -type f | xargs $(CLANG_FORMAT) -i
