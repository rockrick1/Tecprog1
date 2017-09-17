#!/bin/bash

python3 montador $1
make
echo "-------------------------"
./motor