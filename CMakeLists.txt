cmake_minimum_required(VERSION 3.20)

# Project setup (ASM is required for .S files)
project(card-ecg VERSION 1.0 LANGUAGES C ASM)

# Export compile commands (for clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})

# Directories for source files
add_subdirectory(common)
add_subdirectory(src)
add_subdirectory(third-party)

# Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE
    inc
    common
    third-party
)

# Compilation Flags
set(MCU_FLAGS "-mcpu=arm7tdmi")

target_compile_definitions(${PROJECT_NAME} PRIVATE ADUC7060)

target_compile_options(${PROJECT_NAME} PRIVATE
    ${MCU_FLAGS}
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99 -O2 -g -gdwarf-2>
    -ffunction-sections -fdata-sections
    -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith
    -Wredundant-decls -Wshadow -Wcast-qual -Wnested-externs -pedantic
)

# Linker Flags
target_link_options(${PROJECT_NAME} PRIVATE
    ${MCU_FLAGS}
    -nostartfiles
    -T${CMAKE_SOURCE_DIR}/common/aduc706x_rom.ld
    -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map
    -Wl,--cref,--print-memory-usage,--gc-sections
    -specs=nosys.specs
    -fno-exceptions -fno-rtti
)

# Post-Build: Generate .hex and .lss (Matches Makefile behavior)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJDUMP} -dC $<TARGET_FILE:${PROJECT_NAME}> > ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.lss
    COMMENT "Generating .hex and .lss files..."
)

# Quality Assurance Targets (Tests & Static Analysis)
function(add_bash_target NAME SCRIPT_DIR SCRIPT_NAME)
    add_custom_target(${NAME}
        COMMAND bash ${SCRIPT_NAME}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${SCRIPT_DIR}
        USES_TERMINAL
    )
endfunction()

add_bash_target(tests "tests/Ceedling" "unit-tests.sh")
add_bash_target(coverage "tests/Ceedling" "code-coverage.sh")
add_bash_target(clang-tidy "tests/StaticAnalysis" "clang-tidy.sh")
add_bash_target(cppcheck "tests/StaticAnalysis" "cppcheck.sh")
add_bash_target(code-complexity "tests/StaticAnalysis" "code-complexity.sh")
