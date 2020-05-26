#!/bin/bash

set -e

if [ "$1" = "etlegacy" ]; then
	BUILD_WITH='HEADERS_ETLEGACY'
        sed -i '/git_version/d' ../etlegacy/src/qcommon/q_shared.h
else 
	BUILD_WITH='HEADERS_VANILLA'
fi

echo building option $BUILD_WITH

gcc -c -Wall -Werror -fpic ../src/wrapper.c
gcc -shared -o qagame.mp.`uname -m`.so wrapper.o

rm -Rf out/*
cp ../ffi/ffi_build.py .
python3 ffi_build.py $BUILD_WITH
rm -Rf ../src/*.o
mkdir -p out
cp _pyet.so out/
cp qagame.mp.`uname -m`.so out/
cp -R ../plugins out/

