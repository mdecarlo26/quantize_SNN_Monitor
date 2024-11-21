#!/bin/bash

awk '
  /-- Summary/ { in_summary = 1; next }               # Start capturing after "-- Summary" line
  /^-- $/ { if (in_summary) next }                    # Skip lines with just dashes while in Summary section
  /^-- / && in_summary { exit }                       # Stop capturing at the next section divider
  in_summary'                                        # Print only while in Summary section
