#!/bin/bash

# Fix HUGE related error.
grep -rl "HUGE" parsec-2.1/pkgs/apps/ferret | xargs sed -i "s/HUGE/HUGE_VAL/g"
#grep -rl "HUGE" parsec-2.1/pkgs/netapps/netferret | xargs sed -i "s/HUGE/HUGE_VAL/g"

