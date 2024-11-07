#!/bin/bash

# Read from standard input
while IFS= read -r line; do
    # Skip lines that don't contain summary information
    if [[ $line == *"-- Summary"* ]]; then
        read -r line
    fi

    # Print each word in the summary line on a new line, skipping empty values
    echo "$line" | tr -s ' ' '\n' | grep -v '^$'
done
