#!/bin/bash
clear
echo "Multiplication without vectorization"
gcc -o lab1 final.c
./lab1
echo "                                 "
gcc -O3 -msse -fopt-info-vec-optimized -o lab1 final.c
echo "Multiplication with vectorization"
./lab1