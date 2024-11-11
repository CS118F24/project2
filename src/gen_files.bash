#!/bin/bash
openssl genpkey -algorithm ec -pkeyopt ec_paramgen_curve:P-256 -outform DER -out server_key.bin
openssl genpkey -algorithm ec -pkeyopt ec_paramgen_curve:P-256 -outform DER -out ca_key.bin
openssl genpkey -algorithm ec -pkeyopt ec_paramgen_curve:P-256 -outform DER -out ca_key_2.bin
openssl pkey -in ca_key.bin -pubout -outform DER -out ca_public_key.bin

./gen_cert server_key.bin ca_key.bin server_cert.bin
./gen_cert server_key.bin ca_key_2.bin server_cert2.bin
