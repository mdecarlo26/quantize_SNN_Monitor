#!/bin/bash

# Initialize flag to detect if we're in the summary section
in_summary=false

# Read input line by line
while IFS= read -r line; do
  # Check if we hit the "Summary" section
  if [[ $line == *"-- Summary"* ]]; then
    in_summary=true
    continue
  fi

  # If in summary, output the line until we hit the next section
  if $in_summary; then
    # Stop when the line after the summary divider appears
    if [[ $line == *"--------------------------------------------------------------------------------"* ]]; then
      break
    fi
    # Output the summary line
    echo "$line"
  fi
done
