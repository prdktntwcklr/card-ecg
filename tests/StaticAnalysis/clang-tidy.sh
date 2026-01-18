#!/bin/bash

checker=clang-tidy
dummy_file=dummyfile

echo ""
echo " ========================================================= "
echo "     Running Static Code Analysis                          "
echo "     using $checker ...                                    "
echo " ========================================================= "
echo ""

$checker $(find ../../src -name "*.c" -o -name "*.cpp") -header-filter=.* -- -nostdlibinc -mfloat-abi=soft --target=arm -I../../inc -I../../common -I../../third-party -I../../inc/drivers -I../../inc/display -I../../inc/utils > $dummy_file

echo ""
echo " ========================================================= "
echo "     RESULTS                                               "
echo ""

results=$(cat $dummy_file | sed "/^^/d")

rm $dummy_file

if [[ $results ]]; then
    echo "     FAIL                                                  "
    echo "     $checker has found problems!                          "
    echo " ========================================================= "
    echo ""
    echo "$results"
    echo ""
    exit 1
else
    echo "     SUCCESS                                               "
    echo "     $checker says code is OK!                             "
    echo " ========================================================= "
    echo ""
fi

exit 0

echo ""
