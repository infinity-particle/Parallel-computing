#!/bin/bash
clear
echo "Without auto-vectorization"
gcc -o main.out main.c
./main.out
echo "                                 "
gcc -O3 -msse2 -o main.out main.c
echo "With auto-vectorization"
./main.out
