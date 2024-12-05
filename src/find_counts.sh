#!/bin/bash

# Check if exactly two filenames are provided
if [ $# -ne 2 ]; then
  echo "Usage: ./compare.sh filename1 filename2"
  exit 1
fi

# Read the input files
file1=$1
file2=$2

# Ensure both files have the same number of lines
lines_file1=$(wc -l < "$file1")
lines_file2=$(wc -l < "$file2")

if [ "$lines_file1" -ne "$lines_file2" ]; then
  echo "Error: Files do not have the same number of lines."
  exit 1
fi

# Loop through both files line by line
while IFS= read -r line1 && IFS= read -r line2 <&3; do
  # Extract the header and value from both lines
  header1=$(echo "$line1" | awk '{print $1}')
  value1=$(echo "$line1" | awk '{print $2}')
  header2=$(echo "$line2" | awk '{print $1}')
  value2=$(echo "$line2" | awk '{print $2}')
  
  # Ensure that both headers match
  if [ "$header1" == "$header2" ]; then
    # Compute the absolute difference between values
    diff=$((value1 > value2 ? value1 - value2 : value2 - value1))
    echo "$header1 $diff"
  else
    echo "Error: Headers do not match ($header1 vs $header2)"
  fi
done < "$file1" 3< "$file2"
