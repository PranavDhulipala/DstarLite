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
 *  @file Node.hpp
 *  @brief Contains declarations for the Node class which is used to store the x,y coordinates and key values
 *
 *  This file contains Node's functionalities.
 *  Refer Node.cpp for implementation of these functions.
 *
 *
 *
 *
 *
 *  @author Pranav Dhulipala
 *  @date   10/14/2017
 */

#ifndef INCLUDE_NODE_H_
#define INCLUDE_NODE_H_

#include <utility>
#include <iostream>
/**
 * @brief      Class for DstarLite.
 */

class Node {
 public:
  /**
   * @var _x of type int stores the x coordinate of the node
   */
  int _x = 0;
  /**
   * @var _y of type int stores the y coordinate of the node
   */
  int _y = 0;
  /**
   * @var _key of type pair<double,double> stores the key values of the node
   */
  std::pair<double, double> _key = std::make_pair(0, 0);
  /**
   * default constructor
   */
  Node();
  /**
   * Constructor taking 2 parameters
   * @param x of type int used to initialize the value of the member _x
   * @param y of type int used to initialize the value of the member _y
   */
  Node(int x, int y);
  /**
   * Constructor which takes a const Node reference as a parameter copies the values of n in a new Node object
   * @param n is a reference of Node class object
   *
   */
  Node(const Node& n);
  /**
   * @brief Sets the key value of the node
   *
   * @param k is a reference of a pair<double,double>
   * @return void
   */
  void setkey(std::pair<double, double> k);
  /**
   * @brief Gets the value of the key
   * @return the key value of type pair<double,double>
   */
  std::pair<double, double> getkey();
  /**
   * @brief A friend to the class Node. Overloads the operator +, used to add two const Node obejcts
   *
   * @param r a reference of the Node class object
   * @param l a reference of the Node class object
   * @return a const Node created by adding the _x and _y values of the parameters
   */
  friend const Node operator+(const Node &l, const Node &r);
  /**
   * @brief A friend to the class Node.Overloads the operator ==,  used to check if the two const Node elements are the same
   *
   * @param r a reference of the const Node class object
   * @param l a reference of the const Node class object
   * @return a bool value, true if the elements are equal false if different
   */
  friend bool operator==(const Node &l, const Node &r);
  /**
   * @brief A friend to the class Node.Overloads the operator !=,  used to check if the two const Node elements are different
   *
   * @param r a reference of the const Node class object
   * @param l a reference of the const Node class object
   * @return a bool value, true if the elements are not equal false if equal
   */
  friend bool operator!=(const Node &l, const Node &r);

  /**
   * @brief A friend to the class Node.Overloads the operator <,  used to compare the key value of the Node and key
   *
   * @param l a reference of the const Node class object
   * @param r is a key of type pair<double,double>
   * @return a bool value, true or false
   */
  friend bool operator<(const Node& l, const std::pair<double, double> r) {
    if (l._key.first < r.first) {
      return true;
    } else {
      if ((l._key.first == r.first) && (l._key.second < r.second))
        return true;
      else
        return false;
    }
  }
  /**
   * Destructor
   */
  ~Node();
};

#endif  // INCLUDE_NODE_H_
