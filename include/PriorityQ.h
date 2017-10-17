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
 *  @file PriorityQ.hpp
 *  @brief Contains the class definitions and declarations for the template class PriorityQ
 *
 *  This file contains PriorityQ's functionalities.
 *  Used in the DstarLite.cpp
 *
 *
 *
 *
 *
 *  @author Pranav Dhulipala
 *  @date   10/14/2017
 */
#ifndef INCLUDE_PRIORITYQ_H_
#define INCLUDE_PRIORITYQ_H_
#include<queue>
#include<vector>
#include<algorithm>
#include"Node.h"
/**
 * @brief      Structure compare used as the comparator in the PriorityQ making it a min priority queue
 */
struct compare {
  bool operator()(const Node &l, const Node &r) {
    if (l._key.first < r._key.first) {
      return false;
    } else {
      if ((l._key.first == r._key.first) && (l._key.second < r._key.second))
        return false;
      else
        return true;
    }
  }
};
/**
 * @brief      Template Class inherits from priority queue
 */
template<typename T>
class PriorityQ : public std::priority_queue<T, std::vector<T>, compare> {
 public:
  /**
   * @brief A method used to remove a particular value from the queue
   *
   * @param value a const reference to the template T
   * @return bool true or false
   */
  bool remove(const T& value) {
    // finds if the desired value is present in the queue
    auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it != this->c.end()) {
      // used to erase the element
      this->c.erase(it);
      // reorders the queue
      std::make_heap(this->c.begin(), this->c.end(), this->comp);
      return true;
    } else {
      return false;
    }
  }
  /**
   * @brief A method to find if an element is present in the queue
   *
   * @param value a const reference to the template T
   * @return the template T
   */
  T find(const T& value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    return *it;
  }
};
#endif  // INCLUDE_PRIORITYQ_H_
