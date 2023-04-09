#!/bin/bash

checker=cppcheck
dummy_file=dummyfile
addon_file=addon.json

echo ""
echo " ========================================================= "
echo "     Running Static Code Analysis                          "
echo "     using $checker ...                                    "
echo " ========================================================= "
echo ""

addon_option=""

if [[ -f "$addon_file" ]]; then
    addon_option=--addon="$addon_file"
fi

$checker --enable=all --suppress=missingInclude "$addon_option" \
         --inline-suppr --suppressions-list=.cppcheck --language=c \
         --output-file=$dummy_file -I../../inc ../../src -DTEST

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
