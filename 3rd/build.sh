#!/bin/bash

# 相对路径
# SCRIPT_DIR=$(dirname "$0")
# 绝对路径
SCRIPT_DIR=$(readlink -f "$(dirname "$0")")  
MODULE=$(ls "$SCRIPT_DIR" -l | grep '^d' | awk '{print $9}')

echo "SCRIPT_DIR $SCRIPT_DIR"
echo "module list: $MODULE"

build_fmt() {
    cd $SCRIPT_DIR/fmt/
    cmake -B $SCRIPT_DIR/fmt/build -DCMAKE_BUILD_TYPE=Debug
    cmake --build $SCRIPT_DIR/fmt/build --config Debug
    cd $SCRIPT_DIR/fmt/build
    # mingw32-make
}

for module in ${MODULE[@]}; do
    case "$module" in
    "fmt")
        echo "你选择了 option1"
        build_fmt
        ;;
    *)
        echo "INVALID"
        ;;
    esac
done
