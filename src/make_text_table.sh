#!/bin/bash

# Function to add commas to numbers for readability
add_commas() {
  echo "$1" | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta'
}

# Initialize headers and row data
declare -A headers
metrics=("Instruction Reads" "Instruction L1 Cache Misses" "Instruction Last-level Cache Misses" 
         "Data Reads" "Data L1 Cache Misses" "Data Last-level Cache Misses" 
         "Data Writes" "Data L1 Cache Misses on Writes" "Data Last-level Cache Misses on Writes" 
         "Branch Instructions" "Branch Mispredictions" "Branch Indirects" 
         "Branch Indirect Mispredictions" "Integer Operations")

# Prepare the LaTeX table header with metrics as rows
table_header="\\begin{table}[ht]
\\centering
\\begin{tabular}{|l|"

# Read input files
for file in "$@"; do
  # Add file names as columns
  table_header+="r|"
done

table_header+="}
\\hline
\\textbf{Metric} & "

# Add the filenames as column headers in the LaTeX table
for file in "$@"; do
  table_header+="\\textbf{$(basename "$file" .txt)} & "
done

table_header="${table_header%& } \\\\
\\hline"

# Generate the table rows
rows=""
for metric in "${metrics[@]}"; do
  row="$metric & "
  for file in "$@"; do
    # Extract the value from each file
    value=$(grep "$metric" "$file" | awk '{print $NF}')
    # Add commas to the value for readability
    formatted_value=$(add_commas "$value")
    row+="$formatted_value & "
  done
  rows+="${row%& } \\\\
"
done

# Final LaTeX table
cat <<EOF
$table_header
$rows
\\hline
\\end{tabular}
\\caption{Cache and Instruction Metrics for Multiple Programs}
\\label{tab:metrics_multicol}
\\end{table}
EOF
