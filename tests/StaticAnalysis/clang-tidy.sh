#!/bin/bash

CHECKER=clang-tidy
DUMMY_FILE=dummyfile

# Get the directory where the script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo ""
echo " ========================================================= "
echo "     Running Static Code Analysis                          "
echo "     using $CHECKER ...                                    "
echo " ========================================================= "
echo ""

$CHECKER $(find ../../src -name "*.c" -o -name "*.cpp") \
  -p ../../build \
  --config-file="$SCRIPT_DIR/.clang-tidy" \
  -header-filter=".*" > $DUMMY_FILE

echo ""
echo " ========================================================= "
echo "     RESULTS                                               "
echo ""

results=$(cat $DUMMY_FILE | sed "/^^/d")

rm $DUMMY_FILE

if [[ $results ]]; then
    echo "     FAIL                                                  "
    echo "     $CHECKER has found problems!                          "
    echo " ========================================================= "
    echo ""
    echo "$results"
    echo ""
    exit 1
else
    echo "     SUCCESS                                               "
    echo "     $CHECKER says code is OK!                             "
    echo " ========================================================= "
    echo ""
fi

exit 0

echo ""
