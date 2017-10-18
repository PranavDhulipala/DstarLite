## Introduction

- Midterm Project for ENPM808X


[![Build Status](https://travis-ci.org/PranavDhulipala/DstarLite.svg?branch=master)](https://travis-ci.org/PranavDhulipala/DstarLite)
[![Coverage Status](https://coveralls.io/repos/github/PranavDhulipala/DstarLite/badge.svg?branch=master)](https://coveralls.io/github/PranavDhulipala/DstarLite?branch=master)
---

## Overview

This is a simple path planner implemetation in C++ .

The project's objective is to implement a simple path planner namely D* lite which has been very much popular with mobile robot and autonomous vehicle navigation. The problem includes a robot with a known goal position in an unknown terrain and the robot must navigate to the goal avoiding the obstacles. The robot initially assumes that the map is free from obstacles and plans the shortest path from goal to the start position, whenever it comes across a new obstacle which it had no idea about before it adds the information to the map and re-plans a new path from the current position to goal or determine if it is not possible to reach the goal.Planning of a new path when the number of obstacles is high is a bit difficult so to avoid this risk we use incremental heuristics in which the distance to goal is approximated this makes the search focused and build the new solution upon previous solutions. D* Lite can also be used to map the surroundings of a mobile robot, this is done by discretizing the terrain into cells with uniform resolution and then moving the robot from its current cell to the closest cell with unknown traversability, until the terrain is mapped. The assumptions made in this implementation is that the map is a graph with variable edge weights initially the edge weights are set to one but if an obstacle is encountered the edge weight changes to infinity , to illustrate this consider a robot in an environment with obstacles the shortest path between the start and goal would not necessarily be a straight line as generally expected this is because the movement of the robot depends on the location of the obstacles i.e. a cost is associated with the robot’s movement which will imply that straight line is not always the best solution. Another assumption would be to limit the movement of the robot i.e. the robot can only move in a 4 or 8 connected graph.

The module was implemented using three classes: Grid, Node and DstarLite. The grid class overloads the ostream operator which is used to display the grid. The grid class uses a vector of vector char to do so. Initially all the nodes are displayed with u (unexplored) and when the start,goal and obstacles are set these nodes coordinates in the map are changed to s,g and o repectively. The Node calss has the x,y coordinate values and also a key.The DstarLite class has methods used in the planning algorithm. A custom Priority queue is used in the implementation.

The project was done in the C++ leveraging C++ 11/14 features. The code follows the Google C++ Styleguide with cpplint validation. Cppcheck was also used for static code analysis. This project followed Test_driven Development to guide implementation and uses unit tests to test the code coverage written using Google Test framework. The entire code was written and debugged in Eclipse IDE. The code follows doxygen-formatted comments to create doxygen documentation.

The project was completed in two weeks over two sprints which were one week long in durationwithout the use of external libraries. This project was implemented by following the Solo Iterative Process(SIP). This included the creation of a product backlog, UML diagrams.Followed by the creation of unit tests for the planner and implementing the actual path planner. More unit tests were written to cover all possible cases. The final stage involved the fixing the errors and creation of the necessary documentation.

Detailed explanation of the algorithm can be found [here](http://idm-lab.org/bib/abstracts/papers/aaai02b.pdf)

## Product Backlog,Iteration Backlogs and Worklog

Link to the spreadsheet https://docs.google.com/spreadsheets/d/17pHmtAirQ_ssRiRcsVRYO3rvNcxaiY6u7N-sm8TDlV0/edit#gid=0

## License

This program is under MIT License. A copy of the license can be obtained from [here](https://github.com/PranavDhulipala/DstarLite/LICENSE) 

Copyright (c) 2017 Pranav Dhulipala
```bash
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Build Instructions


- Checkout the repo (and submodules)
```bash
$ git clone --recursive https://github.com/PranavDhulipala/DstarLite.git
cd DstarLite
mkdir -p build && cd build
cmake ..
make
```

## Running the demo


- To start the program, in your build directory

```bash
./app/shell-app
```
- An example of the planner can be found [here](https://postimg.org/image/1bnu7kdxcb/)


## Running the unit tests


- In your build directory

```bash
./test/cpp-test
```


## Generating doxygen documentation


- In your git home directory

```bash
doxygen DstarLite
```

- Doxygen files will be generated to /docs folder



