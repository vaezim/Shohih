#! /usr/bin/sh

PROJECT_ROOT_DIR=$(pwd)

# Change -DCMAKE_BUILD_TYPE=Debug for debugging
cmake -DCMAKE_BUILD_TYPE=Release -S $PROJECT_ROOT_DIR -B ${PROJECT_ROOT_DIR}/output/build

make -C ${PROJECT_ROOT_DIR}/output/build -j4