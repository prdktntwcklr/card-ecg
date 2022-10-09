#!/bin/bash

grapher=doxygen
outdir=doxygen

rm -rf $outdir

echo ""
echo " ========================================================= "
echo "     Creating Dependency Graph                             "
echo "     using $grapher ...                                    "
echo " ========================================================= "
echo ""

env OUTPUT_DIRECTORY=$outdir $grapher Doxyfile
