#!/bin/bash

# set thresholds
NLOC=25
CCN=15
PAR=5
LEN=50

echo ""
echo " ========================================================= "
echo "     Running Complexity Analysis                           "
echo "     using lizard ...                                      "
echo ""
echo "     Thresholds:                                           "
echo "     Netto Lines of Code: $NLOC                            "
echo "     Complexity: $CCN                                      "
echo "     Parameters: $PAR                                      "
echo "     Length: $LEN                                          "
echo " ========================================================= "
echo ""

results=$(lizard -w -Tnloc=$NLOC -Tcyclomatic_complexity=$CCN \
          -Tparameter_count=$PAR -Tlength=$LEN --languages c ../src)

echo "Running lizard..."

echo ""
echo " ========================================================= "
echo "     RESULTS                                               "
echo ""

if [[ $results ]]; then
	echo "     FAIL                                                  " 
	echo "     Consider refactoring the following functions:         "
    echo " ========================================================= "
	echo ""
    echo "$results"
	echo ""
	exit 1
else
	echo "     SUCCESS                                               "
	echo "     Your code does not exceed any thresholds.             "
    echo " ========================================================= "
	echo ""
fi

exit 0
