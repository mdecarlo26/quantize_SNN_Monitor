#!/bin/bash

if [ -z "$1" ]; then
	echo "Usage: $0 <compiled C file>"
	exit 1
fi

EXECUTABLE="$1"

if [ ! -f "$EXECUTABLE" ] || [ ! -x "$EXECUTABLE" ]; then
	echo "Error: $EXECUTABLE either does not exist or is not executable."
	exit 1
fi

results_dir="results"

output_file="./${results_dir}/${EXECUTABLE}_results"
summary_file="./${results_dir}/${EXECUTABLE}_summary"

echo "Starting Cachegrind"

valgrind --tool=cachegrind --cachegrind-out-file="$output_file" --cache-sim=yes --branch-sim=yes ./"$EXECUTABLE" > /dev/null 2>&1

echo "Cachegrind output written for $EXECUTABLE to $output_file"

cg_annotate "$output_file" | less > "$summary_file"

rm "$output_file"

echo "Summary results written to $summary_file"
