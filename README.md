---
tags: project
author: PikaChin
title: AStarEngine
---
AStarEngine
===
This project is developped for the final project of NSD in NYCU.

Outline:
[TOC]

## Introduction
A* Search is a path finding algorithm which is usually used in the game development and some graph problem. The difference of A* Search and Dijkstra is that A* Search introduce the heuristic function. The heuristic function, which gives an intuitive of the current state/node to the goal/target.

The algorithm is as following:
![](https://i.imgur.com/0B2EKC9.png)
At the start node, it can found the adjecent node, then calculate the f(node) value. The f(node) value is determined by g(node) and h(node).
g(node) is same with the Dijkstra distance value. h(node) is the heuristic value determined by the user defined heuristic function, for example, Manhattan Distance.
![](https://i.imgur.com/7Og0iPP.png)
Next, try to pop out the node with lowest f(node) value. Tag it as visited, and do the same process as the above.
![](https://i.imgur.com/YMzA8XV.png)
Keep doing the process until reach the target node.

In this project, the logic of A* search is already written with c++. The user can experience A* search through implementing their own environment in c++/python.

The user should follow the environment interface to implement their own game. I will futher explain the interface of the environment in latter part.

## How to Start
The project is written with C++ and Python. The system architecture will show in latter section. Here, you only need to know that the project is build with C++ and bind the C++ library into Python by using Pybind11.

### Build
I suggest you to build the project with the Container:
```bash
podman run \
    -v=$PWD:/workspace \
    -w=/workspace \
    -it \
    --name="A_Star" \
    derrick4563/nsd:latest

# Then cd into the workspace directory
cd /workspace

# Build the project with setup.sh
./script/setup.sh -build
```
:::info
**Hint**: Use docker to run the container is ok, but I prefer podman. The reason for using podman rather than docker you can refer to [this website](https://www.lambdatest.com/blog/podman-vs-docker/).
:::

The setup script will build the project generating test binary executable and pybind library. The pybind library name is **astar_engine** which will be placed into **src/py_env** directory automatically.

Because the pybind library is inside **src/py_env**, the Python environment file should be placed into this directory.

Try to import astar_engine in Python:
```python
# cd /workspace/src/py_env
# python3
import astar_engine
```

If you want to implement your own environment in C++, you must have generate some new cpp file. Therefore, you will need to rebuild the project.
At this moment, you can use the rebuild script:
```bash
./script/rebuild.sh
```

### Run Example

TODO

## Implement Your Own Environment

### Implement in C++

### Implement in Python

## System Architecture
