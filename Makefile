# --- Configuration ---
BUILD_DIR = build

# Path to your toolchain file
TOOLCHAIN = arm-none-eabi.cmake

.PHONY: all build setup clean tests coverage clang-tidy cppcheck code-complexity

# Default target: Configure and then build
all: build

# Build firmware binaries
build: setup
	cmake --build $(BUILD_DIR)

# Rule to run CMake configuration if the build directory doesn't exist
setup:
	mkdir -p $(BUILD_DIR)
	cmake -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)

# Rule to remove the CMake build directory
clean:
	rm -rf $(BUILD_DIR)
	@echo "Build directory removed."

# Delegating to custom targets defined in CMake
tests: setup
	cmake --build $(BUILD_DIR) --target tests

coverage: setup
	cmake --build $(BUILD_DIR) --target coverage

clang-tidy: setup
	cmake --build $(BUILD_DIR) --target clang-tidy

cppcheck: setup
	cmake --build $(BUILD_DIR) --target cppcheck

code-complexity: setup
	cmake --build $(BUILD_DIR) --target code-complexity
