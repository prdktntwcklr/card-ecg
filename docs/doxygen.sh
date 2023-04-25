#!/bin/bash

documentation_tool=doxygen
outdir=.

rm -rf $outdir/html

echo ""
echo " ========================================================= "
echo "     Creating Documentation                                "
echo "     using $documentation_tool ...                         "
echo " ========================================================= "
echo ""

env OUTPUT_DIRECTORY=$outdir $documentation_tool Doxyfile
