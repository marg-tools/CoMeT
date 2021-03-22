#!/bin/bash

# Fix HUGE related error.
grep -rl "HUGE" pkgs/apps/ferret | xargs sed -i "s/HUGE/HUGE_VAL/g"
grep -rl "HUGE" pkgs/netapps/netferret | xargs sed -i "s/HUGE/HUGE_VAL/g"

