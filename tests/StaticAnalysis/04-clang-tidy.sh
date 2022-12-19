#!/bin/bash

echo ""
echo " ========================================================= "
echo "     Running Static Code Analysis                          "
echo "     using clang-tidy ...                                  "
echo " ========================================================= "
echo ""

clang-tidy ../../src/* -checks=*,-hicpp-signed-bitwise,-llvm-header-guard,-readability-avoid-const-params-in-decls,-readability-magic-numbers,-cppcoreguidelines-avoid-magic-numbers -header-filter=.* -- -nostdlibinc --target=arm -I../../inc -I../../common

echo ""
