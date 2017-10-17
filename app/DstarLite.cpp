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
 *  @file DstarLite.cpp
 *  @brief Contains definitions for the planning algorithm
 *
 *  This file has the definitions of the methods used in the D* Lite algorithm
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
#include <algorithm>
#include <utility>
/**
 * @brief Computes the euclidean distance between the current node and the start node
 * @param  n an object of the class node
 * @param  g an object of the class Grid
 * @return a double, the calculated euclidean distance between the
 *         current node and the start node stored in the grid
 */
double DstarLite::heuristic(Node n, Grid g) {
  return (sqrt(pow(n._x - g.start._x, 2) + pow(n._y - g.start._y, 2)));
}
/**
 * @brief        Sets the rhs value of goal to 0, calculates it's key and inserts it in the priority queue
 *
 * @param  grid  reference to an object of class Grid
 * @param  g     reference to a vector of vector double
 * @param  rhs   reference to a vector of vector double
 * @param  km    an integer
 * @return       void
 */
void DstarLite::initialize(Grid grid, std::vector<std::vector<double> > g,
                           std::vector<std::vector<double> > &rhs, int km) {
  // set the rhs value of goal to zero
  rhs[grid.goal._y][grid.goal._x] = 0;
  // calculates the key of goal
  std::pair<double, double> k = calculateKey(grid, grid.goal, g, rhs, km);
  grid.goal.setkey(k);  // set the key of goal
  U.push(grid.goal);  // push goal into the priority queue
}
/**
 * @brief Finds the neighbour of the given node
 *
 * @param  grid reference to an object of the class Grid
 * @param  node reference to an object of the class Node
 * @return vector<Node> a vector of Node objects
 */
std::vector<Node> DstarLite::getNeighbours(Grid grid, Node node) {
  // stores the neighbours of the node
  std::vector<Node> neighbours;
  // used to iterate in the x direction
  std::vector<int> xVal = { -1, -1, -1, 0, 0, 1, 1, 1 };
  // used to iterate in the y direction
  std::vector<int> yVal = { -1, 0, 1, -1, 1, -1, 0, 1 };
  for (size_t i = 0; i < xVal.size(); i++) {
    Node n(node._x + xVal[i], node._y + yVal[i]);
    if (grid.isValid(n)) {
      neighbours.push_back(n);
    }
  }
  return neighbours;  // vector of nodes
}
/**
 * @brief        Calculates the key of the node
 *
 * @param  node  reference to an object of the class Node
 * @param  g     reference to a vector of vector double
 * @param  rhs   reference to a vector of vector double
 * @param  start reference to an object of the class Node
 * @param  km    an integer
 * @return       pair<double,double> Key value
 */
std::pair<double, double> DstarLite::calculateKey(
    Grid grid, Node node, std::vector<std::vector<double> > g,
    std::vector<std::vector<double> > rhs, int km) {
  // sets min value to based on the minimum of node's g and rhs
  double minVal =
      g[node._y][node._x] > rhs[node._y][node._x] ?
          rhs[node._y][node._x] : g[node._y][node._x];
  double key1 = minVal + heuristic(node, grid) + km;
  double key2 = minVal;
  // make pair of key1 and key2
  return std::make_pair(key1, key2);
}
/**
 * @brief        Updates the rhs-values and keys of the potentially affected nodes
 *
 * @param  u     reference to an object of the class Node
 * @param  g     reference to a vector of vector double
 * @param  rhs   reference to a vector of vector double
 * @param  grid  reference to an object of the class Grid
 * @param  km    an integer
 * return        void
 */
void DstarLite::updateVertex(Node u, std::vector<std::vector<double> > g,
                             std::vector<std::vector<double> > &rhs,
                             std::vector<std::vector<double> > cost, Grid grid,
                             int km) {
  if (u != grid.goal) {
    // neighbours of u
    std::vector<Node> neighbourList = getNeighbours(grid, u);
    std::vector<double> valUpdate;
    for (auto n : neighbourList) {
      // stores the updated values of the neighbours of the node u
      valUpdate.push_back(g[n._y][n._x] + cost[n._y][n._x]);
    }
    // rhs is set as the minimum value of the valUpdate
    rhs[u._y][u._x] = *std::min_element(valUpdate.begin(), valUpdate.end());
  }
  // checks if the the node u is present in the priority queue
  if (u == U.find(u)) {
    U.remove(u);  // if found removes the node u
  }
  if (g[u._y][u._x] != rhs[u._y][u._x]) {
    auto key = calculateKey(grid, u, g, rhs, km);  // calculates the key of u
    u.setkey(key);  // sets the key of u
    U.push(u);  // pushes u to the priority queue
  }
}
/**
 * @brief        Computes the shortest path by repeatedly expanding the locally inconsistent nodes in the order of their priorities
 *
 * @param  grid  reference to an object of class Grid
 * @param  g     reference to a vector of vector double
 * @param  rhs   reference to a vector of vector double
 * @param  km    an integer
 * @return       void
 */
void DstarLite::computePath(Grid grid, std::vector<std::vector<double> > &g,
                            std::vector<std::vector<double> > &rhs,
                            std::vector<std::vector<double> > cost, int km) {
  while (U.top() < calculateKey(grid, grid.start, g, rhs, km)
      || (rhs[grid.start._y][grid.start._x] != g[grid.start._y][grid.start._x])) {
    Node u = U.top();  // top Node
    U.pop();  // remove Node
    if (u < calculateKey(grid, u, g, rhs, km)) {
      std::pair<double, double> knew = calculateKey(grid, u, g, rhs, km);
      u.setkey(knew);
      U.push(u);
    } else if (g[u._y][u._x] > rhs[u._y][u._x]) {
      // sets the g value of the node equal to it's rhs value
      g[u._y][u._x] = rhs[u._y][u._x];
      std::vector<Node> neighbours = getNeighbours(grid, u);
      for (auto &n : neighbours) {
        if (cost[n._x][n._y] == 1)
          // updates the inconsitent nodes
          updateVertex(n, g, rhs, cost, grid, km);
      }
    } else {
      // sets the g value to "infinity"
      g[u._y][u._x] = grid._columns * grid._rows + 1;
      std::vector<Node> neighbours = getNeighbours(grid, u);
      for (auto &n : neighbours) {
        // checks the cost of the node
        if (cost[n._x][n._y] == 1)
          // updates the neighbours of the node u
          updateVertex(n, g, rhs, cost, grid, km);
      }
      // updates the node u
      updateVertex(u, g, rhs, cost, grid, km);
    }
  }
}
/**
 * @brief Scans the grid for nodes with potential to be obstacles and sets their cost to infinity
 *
 * @param grid reference to an object of class Grid
 * @param  curr reference to an object of class Node
 * @param  cost reference to a vector of vector double
 * @param  scanRange an integer
 * @return vector<Node> a vector of Node objects
 */
std::vector<Node> DstarLite::scan(Grid grid, Node curr,
                                  std::vector<std::vector<double> > &cost,
                                  int scanRange) {
  std::vector<Node> newSet;
  // used to check the range
  int rangeChecked = 0;
  std::vector<Node> statestoUpdate = getNeighbours(grid, curr);
  rangeChecked = 1;
  while (rangeChecked < scanRange) {
    for (auto state : statestoUpdate) {
      newSet.push_back(state);
      std::vector<Node> n = getNeighbours(grid, state);
      for (auto n1 : n) {
        // checks if the node in the grid is not an obstacle
        if ((grid.grid[n1._y][n1._x] == 'o')) {
          // if obstacle, set the cost to infinity
          cost[n1._y][n1._x] = grid._columns * grid._rows + 1;
          // removes duplicates from the vector
          newSet.erase(
              std::remove_if(newSet.begin(), newSet.end(), [&](const Node& x) {
                return x == n1;
              }),
              newSet.end());
          newSet.push_back(n1);
        } else {
          continue;
        }
      }
    }
    rangeChecked += 1;
    statestoUpdate = newSet;
  }
  return statestoUpdate;
}
