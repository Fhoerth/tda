#!/bin/bash

# Define directories
SRC_DIR="."
EXTENSIONS=("c" "cpp" "h" "sh")
EXCLUDE_DIRS=("*/out/*")

# Check if required formatters are installed
check_formatter() {
	if ! command -v "$1" &>/dev/null; then
		echo "❌ Error: $1 is not installed. Install it using your package manager."
		exit 1
	fi
}

# Install formatters if missing
check_formatter "clang-format"
check_formatter "shfmt"
check_formatter "black"

# Generate exclusion parameters for find
EXCLUDE_PARAMS=()
for dir in "${EXCLUDE_DIRS[@]}"; do
	EXCLUDE_PARAMS+=(! -path "$dir")
done

# Find and format files
echo "🔍 Searching for files to format..."
for ext in "${EXTENSIONS[@]}"; do
	find "$SRC_DIR" -type f -name "*.$ext" "${EXCLUDE_PARAMS[@]}" | while read -r file; do
		echo "🎨 Formatting: $file"
		case "$ext" in
		c | h)
			clang-format -i "$file"
			;;
		sh)
			shfmt -w "$file"
			;;
		py)
			black "$file"
			;;
		esac
	done
done

echo "✅ Formatting complete!"
