#!/bin/bash

input=$(cat)

headers=$(echo "$input" | awk 'NR==2')
data=$(echo "$input" | awk 'NR==3')

IFS=' ' read -r -a names <<< "$(echo "$headers" | sed 's/ \+/n/g' | tr -d '_')"
IFS=' ' read -r -a values <<< "$(echo "$data" | sed 's/ ([^)]*)//g' | tr -d '_')"

for i in "${!names[@]}"; do
	echo "${names[i]} ${values[i]}"
done
