set -e

gcc -c -Wall -Werror -fpic ../src/wrapper.c
gcc -shared -o qagame.mp.`uname -m`.so wrapper.o
cp ../ffi/ffi_build.py .
python3 ffi_build.py
rm ../src/*.o
mkdir -p out
cp _pyet.so out/pyet.so
cp qagame.mp.`uname -m`.so out/
cp ../plugins/plugins.py out/
