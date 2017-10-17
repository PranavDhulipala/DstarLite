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
 *  @file Grid.hpp
 *  @brief Contains declarations for the Grid class
 *
 *  This file contains the Grid's functionalities.
 *  Refer Grid.cpp for implementation of these functions.
 *
 *
 *
 *
 *
 *  @author Pranav Dhulipala
 *  @date   10/14/2017
 */


#ifndef APP_GRID_H_
#define APP_GRID_H_

#include "Node.h"
#include<vector>
#include<queue>
#include<algorithm>

/**
 * @brief      Class for Grid
 */
class Grid {
public:
  /**
   * @var _rows is of type int used to store the number of rows of the grid
   */
  int _rows;
  /**
   * @var _columns is of type int used to store the number of columns of the grid
   */
  int _columns;
  /**
   * @var start is of type Node used to store the start location in the grid
   */
	Node start;
  /**
   * @var goal is of type Node used to store the goal location in the grid
   */
	Node goal;
  /**
   * @var grid is of type vector of vector char used in the display of the grid
   */
  std::vector<std::vector<char>> grid;

  /**
   * Constructor which takes two ints as parameters
   *
   * @param rows is of type int used to initialize the _rows
   * @param columns is of type int used to initialize the _columns
   */

  Grid(int rows, int columns);
  /**
   * @brief  Sets the obstacles in the grid
   *
   * @param tl of type Node whose x and y coordinates are used as the top left corner of the obstacle
   * @param br of type Node whose x and y coordinates are used as the bottom right corner of the obstacle
   * @return void
   */
  void obstacle(Node tl, Node br);  // method for adding obstacle blocks in the grid

  /**
   * @brief Used to check if the Node is a valid one that is whether it is in the grid or not
   *
   * @param curr is of type Node
   * @return bool true if the node's x and y values are in the limits of the grid
   */
  bool isValid(Node curr);
  /**
   * @brief A friend of the class Grid. Overloads the ostream opertor << ,used to display the map
   *
   * @param out is a reference of an ostream object
   * @param g is a reference of a Grid object
   * @return overloads the << operator
   */
  friend std::ostream & operator<<(std::ostream & out, Grid &g);
  /**
   * Destructor
   */
	~Grid();
};



#endif /* APP_GRID_H_ */
