#!/bin/bash

# Initialize flag to detect if we're in the summary section
# in_summary=false
# line_num=0

# # Read input line by line
# while IFS= read -r line; do
#     # Check if we hit the "Summary" section
#     if [[ $line == *"-- Summary"* ]]; then
#     in_summary=true
#     continue
#     fi

#     # If in summary, output the line until we hit the next section
#     if $in_summary; then
#     echo $line
#     # Stop when the line after the summary divider appears
#     if [[ $line == *"--------------------------------------------------------------------------------"* ]]; then
#         break
#     fi
#     # Output the summary line
#     echo "$line"
#     fi
# done
awk '
  /-- Summary/ { in_summary = 1; next }               # Start capturing after "-- Summary" line
  /^-- $/ { if (in_summary) next }                    # Skip lines with just dashes while in Summary section
  /^-- / && in_summary { exit }                       # Stop capturing at the next section divider
  in_summary'                                        # Print only while in Summary section
