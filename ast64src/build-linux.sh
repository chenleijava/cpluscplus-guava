#!/usr/bin/env bash
rm -rf ./*.o
mkdir -p ./bin/astrolog
make -f ./Makefile-Unix
cp ./libastrolog.so ../lib/unix
rm -rf ./*.o