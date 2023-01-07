#!/bin/bash

# run this file from within the Docker container

cd tests/StaticAnalysis/
./01-code-complexity.sh
./02-cppcheck.sh
./03-clang-tidy.sh

cd ../Ceedling
./01-unit-tests.sh
