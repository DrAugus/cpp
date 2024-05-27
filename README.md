# AUGUS CPP

## NOTES

[My website](https://augusmeow.github.io/code/cpp/)

## [RUN](./.github/workflows/cmake.yml)

1. clone `git clone https://github.com/DrAugus/cpp.git`
2. enter the dir `cd cpp`
3. make compile dir and enter `mkdir cmake-linux-debug && cd cmake-linux-debug`
4. cmake `cmake ..`
5. make `make`
6. run `./augus_cpp`

## Project Directory

Some subdirectories can be run independently. Please refer to the `CMakeLists.txt` file in each subdirectory for configuration. All `.cpp` files located in the `src/` directory that contain a `main` function can be run independently.

```
src
├── auguslibs
├── bad_fun
├── bit_dsa
├── caf
├── dsa
├── leetcode
├── linux
├── oatpp
├── practice
├── primer
├── reference
├── stl
├── test
└── training
```
