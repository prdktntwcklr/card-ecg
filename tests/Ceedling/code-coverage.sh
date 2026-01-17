#!/bin/bash

set -eou pipefail

TEST_FRAMEWORK=ceedling
FORMATTER=pycobertura
SCRIPT_DIR=$(dirname "$(realpath "$0")")
COVERAGE_DIR="$SCRIPT_DIR/build/artifacts/gcov/gcovr"

echo ""
echo " ========================================================= "
echo "     Creating code coverage report                         "
echo "     using $TEST_FRAMEWORK ...                             "
echo " ========================================================= "
echo ""

$TEST_FRAMEWORK gcov:all

echo ""
echo " ========================================================= "
echo "     Formatting code coverage report                       "
echo "     using $FORMATTER ...                                  "
echo " ========================================================= "
echo ""

echo ${COVERAGE_DIR}
cd ${COVERAGE_DIR}
$FORMATTER show GcovCoverageCobertura.xml --format markdown --output GcovCoverageResults.md
