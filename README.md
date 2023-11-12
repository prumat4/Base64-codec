# base64-codec
The project structure includes a single header file `(base64.hpp)` containing class declarations for Base64, Decoder, and Coder, and separate implementation files `(base64.cpp, decoder.cpp, coder.cpp)` for each class.

## Software requirements (optional)
Cmake && c++11

## Build and run
1. create build directory
```bash
mkdir build && cd build
```

2. build and run demo programm
```bash
cmake .. && make && ./main
```
```diff
-IF U DON'T WANT TO INSTALL CMAKE, YOU CAN SIMPLY RUN THIS COMMANDS IN THE ROOT DIRECTORY
g++ -std=c++17 main.cpp base64/base64.cpp base64/coder.cpp base64/decoder.cpp -o main
./main
```
