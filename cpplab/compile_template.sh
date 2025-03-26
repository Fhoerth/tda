#!/bin/sh

if [ $# -ne 1 ]; then
	echo "Usage: ./compile.sh <filename>"
	exit 1
fi

EXE_NAME="$1"
FLAGS="-std=c++17 -O2"

if [ -f flags.txt ]; then
	FLAGS=$(cat flags.txt)
fi

mkdir -p out

echo "Compiling with: g++ $FLAGS $EXE_NAME.cpp -o out/$EXE_NAME"
g++ $FLAGS "$EXE_NAME.cpp" -o "out/$EXE_NAME"
