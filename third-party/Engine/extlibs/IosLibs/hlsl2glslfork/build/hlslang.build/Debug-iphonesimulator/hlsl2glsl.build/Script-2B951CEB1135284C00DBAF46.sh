#!/bin/sh
cd hlslang/MachineIndependent
flex -ogen_hlslang.cpp hlslang.l
bison -o hlslang_tab.cpp -d -t -v hlslang.y
mv hlslang_tab.hpp hlslang_tab.h
