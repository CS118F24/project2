#!/bin/bash
openssl genpkey -algorithm ec -pkeyopt ec_paramgen_curve:P-256 -outform DER -out server_key.bin
openssl genpkey -algorithm ec -pkeyopt ec_paramgen_curve:P-256 -outform DER -out server_key2.bin
openssl genpkey -algorithm ec -pkeyopt ec_paramgen_curve:P-256 -outform DER -out ca_key.bin
openssl genpkey -algorithm ec -pkeyopt ec_paramgen_curve:P-256 -outform DER -out ca_key2.bin
openssl pkey -in ca_key.bin -pubout -outform DER -out ca_public_key.bin
openssl pkey -in ca_key2.bin -pubout -outform DER -out ca_public_key2.bin

../src/gen_cert server_key.bin ca_key.bin server_cert.bin

rm ca_key.bin ca_key2.bin 
