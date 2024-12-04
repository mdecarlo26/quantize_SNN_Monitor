#!/bin/bash

# Initialize variables for headers and their values
declare -A headers=(
  ["Ir"]="Instruction Reads"
  ["I1mr"]="Instruction L1 Cache Misses"
  ["ILmr"]="Instruction Last-level Cache Misses"
  ["Dr"]="Data Reads"
  ["D1mr"]="Data L1 Cache Misses"
  ["DLmr"]="Data Last-level Cache Misses"
  ["Dw"]="Data Writes"
  ["D1mw"]="Data L1 Cache Misses on Writes"
  ["DLmw"]="Data Last-level Cache Misses on Writes"
  ["Bc"]="Branch Instructions"
  ["Bcm"]="Branch Mispredictions"
  ["Bi"]="Branch Indirects"
  ["Bim"]="Branch Indirect Mispredictions"
)

# Initialize variables for processing
Ir=0
sum_other_values=0

# Read input line by line
while read -r line; do
  # Extract the key and value
  key=$(echo "$line" | awk '{print $1}')
  value=$(echo "$line" | awk '{print $2}')
  
  # Check if the key is valid and process it
  if [[ -n "${headers[$key]}" ]]; then
    if [[ "$key" == "Ir" ]]; then
      Ir=$value
    else
      sum_other_values=$((sum_other_values + value))
    fi
    # Print the full name and value
    echo "${headers[$key]}: $value"
  fi
done

# Calculate Integer Operations
integer_operations=$((Ir - sum_other_values))

# Print the calculated integer operations
echo "Integer Operations: $integer_operations"
