# CompTechQR
This repository provides functions to perform QR iterations and QR
decomposition using the Gram-Schmidt process.

The functions used to perform QR iterations and QR decomposition are located inside
the eigen_qr.c while matlib.c provides matrix utility functions.
main.c is a small demo program which takes input from the input.txt
file and runs qr decomposition and qr iterations. More details
about the input and output format are specified inside the main.c file.
Instructions for running the demo:

cd src
make target
./eigen_qr

A small test suite is provided inside the eigen_qr_test.c file while the test 
files are located inside the test_data directory. 
Instructions for running the tests:

cd src
make tests
./eigen_qr_tests
