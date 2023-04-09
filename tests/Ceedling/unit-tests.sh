#!/bin/bash

test_framework=ceedling

echo ""
echo " ========================================================= "
echo "     Running Unit Tests                                    "
echo "     using $test_framework ...                             "
echo " ========================================================= "
echo ""

$test_framework clobber
$test_framework
