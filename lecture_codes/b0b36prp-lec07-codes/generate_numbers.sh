#!/usr/bin/env bash

for i in $( seq 1 10 ); do echo -n "" $[ ( $RANDOM % 20 ) +1 ]; done 
echo ""
