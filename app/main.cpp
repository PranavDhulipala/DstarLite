/*
 *MIT License
 *
 *  Copyright (c) 2017 Pranav Dhulipala
 *
 *  AUTHOR : PRANAV DHULIPALA
 *  AFFILIATION : UNIVERSITY OF MARYLAND COLLEGE PARK
 *  EMAIL : PRANAV95@UMD.EDU
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 *
 *
 *  Program: Basic implementation of D* Lite
 *
 */
/**
 *  @file main.cpp
 *  @brief Contains the implementation of the planning algorithm
 *
 *  This file contains the planner's main() function
 *
 *
 *
 *
 *
 *
 *  @author Pranav Dhulipala
 *  @date   10/14/2017
 */
#include "DstarLite.h"
#include <vector>
int main() {
  Node start(20, 6);  // sets the start Node
  Node goal(6, 41);  // sets the goal Node
  Node tl(5, 7);  // sets the top corner of the obstacle
  Node br(20, 11);  // sets the bottom corner of the obstacle
  int km = 0;  // an int added to the key value
  Grid grid(51, 51);  // sets the size of the grid
  grid.start = start;
  grid.goal = goal;
  grid.obstacle(tl, br);
  DstarLite dsl;
  Node last = start;
  // g values
  std::vector<std::vector<double> > g(
      grid._rows,
      std::vector<double>(grid._columns, grid._rows * grid._columns + 1));
  // rhs values
  std::vector<std::vector<double> > rhs(
      grid._rows,
      std::vector<double>(grid._columns, grid._rows * grid._columns + 1));
  // costs
  std::vector<std::vector<double> > cost(grid._rows,
                                         std::vector<double>(grid._columns, 1));
  dsl.initialize(grid, g, rhs, km);
  dsl.computePath(grid, g, rhs, cost, km);
  while (start != goal) {
    std::vector<Node> neighbours1 = dsl.getNeighbours(grid, start);
    std::vector<double> costRange;  // used to store the costs of neighbours
    for (auto n : neighbours1) {
      costRange.push_back(g[n._y][n._x] + cost[n._y][n._x]);
    }
    size_t index = 0;
    for (size_t i = 0; i < costRange.size(); i++) {
      if (costRange[index] > costRange[i])
        // index of costRange with minimum value
        index = i;
    }
    // argmin of the neighbours of start
    Node nextStep = neighbours1[index];
    // std::cout << nextStep;
    // break;
    int y1 = nextStep._y;
    int x1 = nextStep._x;
    if (grid.grid[y1][x1] == 'u') {
      start = nextStep;
      int y2 = start._y;
      int x2 = start._x;
      grid.grid[y2][x2] = 'x';
    } else {
      km += dsl.heuristic(last, grid);
      last = start;
      // set the value of nextStep to infinity
      cost[nextStep._y][nextStep._x] = grid._rows * grid._columns + 1;
      std::vector<Node> neighbours2 = dsl.scan(grid, nextStep, cost, 2);
      for (auto n : neighbours2)
        if (grid.grid[n._y][n._x] == 'o') {
          dsl.updateVertex(n, g, rhs, cost, grid, km);
        }
      dsl.computePath(grid, g, rhs, cost, km);
    }
  }
  std::cout << grid;  // print the final grid
  return 0;
}

