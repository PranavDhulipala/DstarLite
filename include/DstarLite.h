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
 *  @file DstarLite.hpp
 *  @brief Contains declarations for the planning algorithm
 *
 *  This file contains DstarLite's functionalities.
 *  Refer DstarLite.cpp for implementation of these functions.
 *
 *
 *
 *
 *
 *  @author Pranav Dhulipala
 *  @date   10/14/2017
 */
#ifndef INCLUDE_DSTARLITE_H_
#define INCLUDE_DSTARLITE_H_
#include "Node.h"
#include "Grid.h"
#include <algorithm>
#include "PriorityQ.h"
#include <cmath>
#include <utility>
#include <vector>
/**
 * @brief      Class for DstarLite.
 */
class DstarLite {
 public:
  /**
   * @brief       Computes the euclidean distance between the current node and the start node
   * @param  n    an object of the class node
   * @param  g    an object of the class Grid
   * @return      a double, the calculated euclidean distance between the current node and the start node stored in the grid
   */
  double heuristic(Node n, Grid g);
  /**
   * @brief        Sets the rhs value of goal to 0, calculates it's key and inserts it in the priority queue
   *
   * @param  grid  reference to an object of class Grid
   * @param  g     reference to a vector of vector double
   * @param  rhs   reference to a vector of vector double
   * @param  km    an integer
   * @return       void
   */
  void initialize(Grid grid, std::vector<std::vector<double> > g,
                  std::vector<std::vector<double> > &rhs, int km);
  /**
   * @brief        Finds the neighbour of the given node
   *
   * @param  grid  reference to an object of the class Grid
   * @param  node  reference to an object of the class Node
   * @return       vector<Node> a vector of Node objects
   */
  std::vector<Node> getNeighbours(Grid grid, Node node);
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
  std::pair<double, double> calculateKey(Grid grid, Node node,
                                         std::vector<std::vector<double> > g,
                                         std::vector<std::vector<double> > rhs,
                                         int km);
  /**
   * @brief        Updates the rhs-values and keys of the potentially affected nodes
   *
   * @param  u     reference to an object of the class Node
   * @param  g     reference to a vector of vector double
   * @param  rhs   reference to a vector of vector double
   * @param  grid  reference to an object of the class Grid
   * @param  km    an integer
   */
  void updateVertex(Node u, std::vector<std::vector<double> > g,
                    std::vector<std::vector<double> > &rhs,
                    std::vector<std::vector<double> > cost, Grid grid,
                    int km);
  /**
   * @brief        Computes the shortest path by repeatedly expanding the locally inconsistent nodes in the order of their priorities
   *
   * @param  grid  reference to an object of class Grid
   * @param  g     reference to a vector of vector double
   * @param  rhs   reference to a vector of vector double
   * @param  km    an integer
   * @return       void
   */
  void computePath(Grid grid, std::vector<std::vector<double> > &g,
                   std::vector<std::vector<double> > &rhs,
                   std::vector<std::vector<double> > cost, int km);
  /**
   * @var U is an object of the PriorityQ
   */
  PriorityQ<Node> U;
  /**
   * @brief               Scans the grid for nodes with potential to be obstacles and sets their cost to infinity
   *
   * @param  grid         reference to an object of class Grid
   * @param  curr         reference to an object of class Node
   * @param  cost         reference to a vector of vector double
   * @param  scanRange    an integer
   * @return              vector<Node> a vector of Node objects
   */
  std::vector<Node> scan(Grid grid, Node curr,
                         std::vector<std::vector<double> > &cost,
                         int scanRange);
};
#endif  // INCLUDE_DSTARLITE_H_

