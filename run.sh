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

# $1 dir $2 cmake type
_cmake(){
    echo ">>> cmake" && echo " "
    cmake -B $1/build -DCMAKE_BUILD_TYPE=$2
    cmake --build $1/build --config $2
    echo " "
}

if [ $# -eq 1 ]; then
    [[ "$1" = "-d" ]] && _cmake $WORKDIR 'Debug' && exit 1
    
    # path, $1 include '/'
    if [[ $1 =~ "/" ]]; then
        _cmake $1 'Debug' && exit 1 
    fi

    exit 1
fi

for type in ${BUILD_TYPE[@]}
do
    _cmake $WORKDIR $type
done

