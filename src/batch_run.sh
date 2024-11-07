#!/bin/bash

if [ "$#" -eq 0 ]; then
	echo "Usage: $0 <C executable 1> <C executable 2> ..."
	exit 1
fi

YELLOW='\033[1;33m'
NC='\033[0m'

for EXECUTABLE in "$@"; do
	if [ -f "$EXECUTABLE" ] && [ -x "$EXECUTABLE" ]; then
		./data_script.sh "$EXECUTABLE"
	else
		echo -e "${YELLOW}Warning:${NC} $EXECUTABLE either does not exist or is not executable"
	fi
done
