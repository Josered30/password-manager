if [ -d ./build ]; then rm -r ./build; fi
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug 
make
