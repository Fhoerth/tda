#!/bin/bash

set -e  # Exit immediately on error

# List of .tex files to compile (hardcoded)
files=("Guia3.tex")

# Create output directory if it doesn't exist
mkdir -p out

# Copy all .tex files and Macros.tex into ./out
cp ./*.tex ./out/
cp ./Macros.tex ./out/ 2>/dev/null || true

# Move to the output directory
cd out

# Compile each .tex file with pdflatex + shell-escape
for file in "${files[@]}"; do
  echo "📄 Compiling $file..."
  pdflatex --shell-escape -interaction=nonstopmode "$file"
done

echo "✅ Build completed."
