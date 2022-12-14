#!/bin/bash

usage="Usage: setup.sh [no option|-build]"

if [ $# == 2 ]; then
    if [ "$1" == "-h" ]; then
        echo $usage
        exit
    elif [ "$1" != "-build" ]; then
        echo "wrong option"
        echo $usage
        exit
    fi
fi

mkdir /workspace/build
cd /workspace/build
cmake ..
if [ "$1" == "-build" ]; then
    make -j
    cp astar_engine.* /workspace/src/py_env
fi
