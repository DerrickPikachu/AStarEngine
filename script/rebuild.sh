#!/bin/bash

cd /workspace/build
make -j
cp astar_engine.* /workspace/src/py_env
