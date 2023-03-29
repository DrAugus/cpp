#!/bin/bash

BUILD_TYPE=(
Debug
Release
)
CPP_TYPE=(
gcc
clang
)

WORKDIR=$(cd "$(dirname "$0")"; pwd)

for type in ${BUILD_TYPE[@]}
do
    echo ">>> cmake $name" && echo " "
    cmake -B ${WORKDIR}/build -DCMAKE_BUILD_TYPE=${type}
    cmake --build ${WORKDIR}/build --config ${type}
    echo " "
done

