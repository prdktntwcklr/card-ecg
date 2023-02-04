#!/bin/bash

test_framework=ceedling

echo ""
echo " ========================================================= "
echo "     Creating code coverage report                         "
echo "     using $test_framework ...                             "
echo " ========================================================= "
echo ""

$test_framework gcov:all utils:gcov
