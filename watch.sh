#!/bin/bash
./build.sh

echo "\n"
echo "\n"
clear

echo "📡 Watching changes in *.tex files..."
fswatch -o ./*.tex | while read _; do
  echo "📦 Compiling..."
  ./build.sh
  echo "✅ Compiled!"
done
