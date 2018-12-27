#!/usr/bin/env bash
rm -rf ./*.o
make -f ./Makefile-MAC
cp -f ./libastrolog.a ../lib/apple
cp -r ./*.h ./astrolog.as ../include/astrolog
rm -rf ./*.o
rm -rf ./libastrolog.a


