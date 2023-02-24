#!/bin/bash

test_framework=ceedling
formatter=pycobertura

echo ""
echo " ========================================================= "
echo "     Creating code coverage report                         "
echo "     using $test_framework ...                             "
echo " ========================================================= "
echo ""

$test_framework gcov:all utils:gcov

echo ""
echo " ========================================================= "
echo "     Formatting code coverage report                       "
echo "     using $formatter ...                                  "
echo " ========================================================= "
echo ""

cd build/artifacts/gcov/
$formatter show GcovCoverageCobertura.xml --format markdown --output GcovCoverageResults.md
