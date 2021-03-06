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
 * @file test.cpp
 *
 *
 * @brief Unit tests for the path planner project
 *
 *  This file contains implementation of unit tests for this project
 *
 * @author Pranav Dhulipala
 * @version 1.0
 */
#include <gtest/gtest.h>
#include <utility>
#include <iostream>
#include <vector>
#include "../include/Node.h"
#include "../app/Node.cpp"
#include "../include/Grid.h"
#include "../app/Grid.cpp"
#include "../include/DstarLite.h"
#include "../app/DstarLite.cpp"

/**
 * @brief      Checks if the coordinates of Node are not negative.
 *
 *
 *
 */
TEST(NodeTest, NotNegative) {
  int x = 2, y = 5;
  Node node(x, y);
  if (node._x < 0 || node._y < 0) {
    ASSERT_GE(node._x, 0);
    ASSERT_GE(node._y, 0);
  }
}
/**
 * @brief      Checks if the key values of the Node are not negative.
 *
 *
 *
 */
TEST(NodeKeyTest, NotNegative) {
  double k1 = 100, k2 = 50;
  std::pair<double, double> key = std::make_pair(k1, k2);
  if (key.first < 0 || key.second < 0) {
    ASSERT_GT(key.first, 0);
    ASSERT_GT(key.second, 0);
  }
}
/**
 * @brief      Checks if the operator overloading of +,== work.
 *
 *
 *
 */
TEST(NodeEqualTest, Equal) {
  Node n1(2, 4), n2(3, 6), n3(5, 10);
  ASSERT_EQ((n1 + n2), n3);
}
/**
 * @brief checks if the node default
 *        constructor initializes
 *        _x,_y as 0
 */
TEST(NodeDefaultTest, True) {
  Node n1, n2(12, 34);
  EXPECT_FALSE(n1 == n2);
}
/**
 * @brief checks the constructor taking Node objects functionality
 */
TEST(NodeConstructorTest, Equal) {
  Node n1(21, 3);
  Node n2(n1);
  EXPECT_EQ(n1, n2);
}
/**
 * @brief checks the setkey and getkey methods
 */
TEST(NodeKeyTest, True) {
  Node n1(2, 4);
  std::pair<double, double> key = std::make_pair(12, 43);
  n1.setkey(key);
  EXPECT_TRUE(n1.getkey() == key);
}
/**
 * @brief checks if the key value is less than
 *        second key value
 */
TEST(NodeKeyCompare, LessThan) {
  Node n1(2, 4);
  std::pair<double, double> key = std::make_pair(12, 43);
  n1.setkey(key);
  std::pair<double, double> key2 = std::make_pair(12, 50);
  EXPECT_LT(n1, key2);
}
/**
 * @brief checks if the key value is less than
 *        second key value
 */
TEST(NodeKeyCompare, True) {
  Node n1(2, 4);
  std::pair<double, double> key = std::make_pair(12, 43);
  n1.setkey(key);
  std::pair<double, double> key2 = std::make_pair(14, 50);
  EXPECT_TRUE(n1 < key2);
}
/**
 * @brief checks if the key value is less than
 *        second key value
 */
TEST(NodeKeyCompare, False) {
  Node n1(2, 4);
  std::pair<double, double> key = std::make_pair(12, 43);
  n1.setkey(key);
  std::pair<double, double> key2 = std::make_pair(1, 5);
  EXPECT_FALSE(n1 < key2);
}
/**
 * @brief      Checks if the operator overloading of +,!= work.
 *
 *
 *
 */
TEST(NodeNotEqualTest, NotEqual) {
  Node n1(12, 4), n2(3, 16), n3(5, 20);
  ASSERT_NE((n1 + n2), n3);
}
/**
 * @brief      Checks if the Node is in the obstacle.
 *             Checks the obstacle method.
 *
 *
 *
 */
TEST(ObstacleCheck, InObstacle) {
  Node n(5, 20), tl(5, 10), br(12, 22);
  Grid grid(50, 50);
  grid.obstacle(tl, br);
  ASSERT_EQ(grid.grid[n._y][n._x], 'o');
}
/**
 * @brief      Checks if the Node is valid.
 *             Checks the isValid function.
 *
 *
 *
 */
TEST(NodeValid, Valid) {
  Grid grid(50, 50);
  Node n(100, 100);
  ASSERT_FALSE(grid.isValid(n));
}
/**
 * @brief      Checks if the value returned by
 *             the heuristic function is equal to
 *             the known value.
 *             Checks the heuristic function.
 *
 *
 */
TEST(HeuristicValue, Equal) {
  DstarLite dsl;
  Grid grid(50, 50);
  Node start(23, 34);
  grid.start = start;
  EXPECT_EQ(dsl.heuristic(start, grid), 0);
}
/**
 * @brief      Checks if the priority queue
 *             sorts the Nodes based on the
 *             key values, is equal to the known
 *             Node with lowest key values.
 *             Checks if the comparator of PriorityQ works.
 */
TEST(PriorityQMinTest, MinElementEqual) {
  DstarLite dsl;
  Node n1(2, 4), n2(4, 4), n3(6, 7), n4(23, 34), n5(12, 42);
  std::pair<double, double> k1 = std::make_pair(2, 44);
  std::pair<double, double> k2 = std::make_pair(23, 44);
  std::pair<double, double> k3 = std::make_pair(23, 1);
  std::pair<double, double> k4 = std::make_pair(213, 44);
  std::pair<double, double> k5 = std::make_pair(2, 4);
  n1.setkey(k1);
  n2.setkey(k2);
  n3.setkey(k3);
  n4.setkey(k4);
  n5.setkey(k5);
  dsl.U.push(n1);
  dsl.U.push(n2);
  dsl.U.push(n3);
  dsl.U.push(n4);
  dsl.U.push(n5);
  EXPECT_EQ(n5, dsl.U.top());
}
/**
 * @brief      Checks if the priority queue
 *             contains the removed Node.
 *             Checks the remove and find methods of
 *             the PriorityQ.
 *
 */
TEST(PriorityQFindElementTest, ElementNotFound) {
  DstarLite dsl;
  Node n1(2, 4), n2(4, 4), n3(6, 7), n4(23, 34), n5(12, 42);
  dsl.U.push(n1);
  dsl.U.push(n2);
  dsl.U.push(n3);
  dsl.U.push(n4);
  dsl.U.push(n5);
  dsl.U.remove(n4);
  EXPECT_TRUE(n4 != dsl.U.find(n4));
}
/**
 * @brief checks the struct compare
 */
TEST(ComparatorTest, False) {
  Node n1(23, 12), n2(2, 4);
  std::pair<double, double> k1 = std::make_pair(2, 44);
  std::pair<double, double> k2 = std::make_pair(23, 44);
  n1.setkey(k1);
  n2.setkey(k2);
  compare c1;
  EXPECT_FALSE(c1(n1, n2));
}
/**
 * @brief checks the struct compare
 */
TEST(ComparatorTest, True) {
  Node n1(23, 12), n2(23, 4);
  std::pair<double, double> k1 = std::make_pair(2, 44);
  std::pair<double, double> k2 = std::make_pair(23, 44);
  n1.setkey(k1);
  n2.setkey(k2);
  compare c1;
  EXPECT_FALSE(c1(n1, n2));
}
/**
 * @brief checks the struct compare
 */
TEST(ComparatorTest, AlsoFalse) {
  Node n1(23, 12), n2(23, 4);
  std::pair<double, double> k1 = std::make_pair(2, 44);
  std::pair<double, double> k2 = std::make_pair(2, 47);
  n1.setkey(k1);
  n2.setkey(k2);
  compare c1;
  EXPECT_FALSE(c1(n1, n2));
}
/**
 * @brief      Checks if the priority queue
 *             contains the removed Node.
 *
 *
 *
 */
TEST(PriorityQRemoveElementTest, False) {
  DstarLite dsl;
  Node n1(2, 4), n2(4, 4), n3(6, 7), n4(23, 34), n5(12, 42);
  dsl.U.push(n1);
  dsl.U.push(n2);
  dsl.U.push(n3);
  dsl.U.push(n4);
  EXPECT_FALSE(dsl.U.remove(n5));
}
/**
 * @brief checks operator << overload
 */
TEST(OstreamTest, True) {
  Node start(1, 2);
  Grid g(10, 10);
  Node goal(8, 3);
  g.goal = goal;
  g.start = start;
  Node x(4, 3);
  g.grid[x._x][x._y] = 'x';
  Node tl(3, 5), br(5, 6);
  g.obstacle(tl, br);
  ASSERT_TRUE(std::cout << g);
}
/**
 * @brief checks if initialize method works
 *        by checking if the goal rhs is set to 0
 */
TEST(InitializeTest, Equal) {
  Node start(1, 2);
  Grid grid(10, 10);
  Node goal(8, 3);
  grid.goal = goal;
  grid.start = start;
  int km = 0;
  DstarLite dsl;
  std::vector<std::vector<double> > g(
      grid._rows,
      std::vector<double>(grid._columns, grid._rows * grid._columns + 1));
  std::vector<std::vector<double> > rhs(
      grid._rows,
      std::vector<double>(grid._columns, grid._rows * grid._columns + 1));
  dsl.initialize(grid, g, rhs, km);
  ASSERT_EQ(rhs[grid.goal._y][grid.goal._x], 0);
}
/**
 * @brief checks the functionality of the neighbour method
 *        by checking if all the 8 neighbours are returned
 */
TEST(NeighbourTest, Equal) {
  Node start(5, 4);
  Grid grid(10, 10);
  DstarLite dsl;
  std::vector<Node> neighbours = dsl.getNeighbours(grid, start);
  size_t n = 8;
  ASSERT_EQ(neighbours.size(), n);
}
/**
 * @brief checks the functionality of calculate key
 *        by comparing the key values
 *
 */
TEST(CalculateKeyTest, LessThan) {
  DstarLite dsl;
  Grid grid(10, 10);
  int km = 1000;
  Node s(3, 4);
  grid.start = s;
  Node m(5, 6);
  std::vector<std::vector<double> > g(
      grid._rows,
      std::vector<double>(grid._columns, grid._rows * grid._columns + 1));
  std::vector<std::vector<double> > rhs(
      grid._rows,
      std::vector<double>(grid._columns, grid._rows * grid._columns + 1));
  std::pair<double, double> key = dsl.calculateKey(grid, m, g, rhs, km);
  EXPECT_LE(key.second, key.first);
}
/**
 * @brief checks the functionality of Scan methods
 *        by checking the vector size returned
 *        is greater than 8 the node's actual
 *        neighbours
 */
TEST(ScanTest, NotEqual) {
  Node start(1, 2);
  Node curr(7, 7);
  Grid g(10, 10);
  Node goal(8, 3);
  g.goal = goal;
  g.start = start;
  Node x(4, 3);
  Node tl(3, 5), br(5, 6);
  g.obstacle(tl, br);
  int range = 2;
  size_t nei = 8;
  DstarLite dsl;
  std::vector<std::vector<double> > cost(g._rows,
                                         std::vector<double>(g._columns, 1));
  std::vector<Node> list = dsl.scan(g, curr, cost, range);
  EXPECT_GT(list.size(), nei);
}
/**
 * @brief  checks if the compute path and updateVertex methods
 *         work by checking the initial rhs value of the last node and its
 *         new value after running the functions
 */
TEST(ComputePathTest, Notequal) {
  Node start(20, 6);
  Node goal(6, 41);
  Node tl(5, 7);
  Node br(20, 11);
  int km = 0;
  Grid grid(51, 51);
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
  double rhsOld = rhs[last._y][last._x];
  // costs
  std::vector<std::vector<double> > cost(grid._rows,
                                         std::vector<double>(grid._columns, 1));
  dsl.initialize(grid, g, rhs, km);
  dsl.computePath(grid, g, rhs, cost, km);
  EXPECT_NE(rhsOld, rhs[last._y][last._x]);
}
