mkdir sql
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -G Ninja -S . -B ./cmake-build-debug
cmake --build cmake-build-debug --target lp-server-oatpp-exe
./bin/lp-server-oatpp-exe