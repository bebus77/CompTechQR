# CompTechQR
Provides functions for performing QR iterations and QR
decomposition using Gram-Schmidt process.

Functions for performing QR iterations and QR decomposition are located inside
the eigen_qr.c while matlib.c provides matrix utility functions.
main.c is a small demo program which takes input from the input.txt
file and runs qr decomposition and qr iterations. More details
about the input and output format are specified inside the main.c file.
Instructions for running demo:

cd src
make target
./eigen_qr

Small test suite is provided inside the eigen_qr_test.c file while the test 
files are located inside the test_data directory. 
Instructions for running tests:

cd src
make tests
./eigen_qr_tests
