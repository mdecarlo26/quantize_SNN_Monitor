#!/bin/bash

input=$(cat)

headers=$(echo "$input" | awk 'NR==2')
values=$(echo "$input" | awk 'NR==4')

headers=$(echo "$headers" | sed 's/_\+//g')  # Remove underscores
values=$(echo "$values" | sed 's/,//g; s/([0-9.]\+%)//g; s/PROGRAM TOTALS//g')  # Remove commas, percentages, and PROGRAM TOTALS

# Convert headers and values into arrays
IFS=' ' read -ra header_array <<< "$headers"
IFS=' ' read -ra value_array <<< "$values"

for i in "${!header_array[@]}"; do
  echo "${header_array[$i]} ${value_array[$i]}"
done