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

