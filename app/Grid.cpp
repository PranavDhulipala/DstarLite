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
 *  @file Grid.cpp
 *  @brief Contains definitions for the Grid class
 *
 *  This file contains the definitions of the Grid's functionalities.
 *
 *
 *
 *
 *
 *  @author Pranav Dhulipala
 *  @date   10/14/2017
 */


#include "Grid.h"

/**
 * Constructor which takes two ints as parameters
 *
 * @param rows is of type int used to initialize the _rows
 * @param columns is of type int used to initialize the _columns
 */

Grid::Grid(int rows, int columns)
    : _rows(rows),  // initializes _row
      _columns(columns),  // initializes _columns
      start(-1, -1),  //initializes the start node
      goal(-1, -1) {  //initializes the goal node
  grid.resize(rows, std::vector<char>(columns, 'u'));  // sets the size of the vector<vector<char>> and initializes it with u(unknown)
}

/**
 * @brief  Sets the obstacles in the grid
 *
 * @param tl of type Node whose x and y coordinates are used as the top left corner of the obstacle
 * @param br of type Node whose x and y coordinates are used as the bottom right corner of the obstacle
 * @return void
 */

void Grid::obstacle(Node tl, Node br) {
  auto x1 = std::min(tl._x, br._x);
  auto x2 = std::max(tl._x, br._x);
  auto y1 = std::min(tl._y, br._y);
  auto y2 = std::max(tl._y, br._y);


  for (auto row = y1; row <= y2; ++row) {
    for (auto col = x1; col <= x2; ++col) {
      grid[row][col] = 'o';
    }
  }
}


/**
 * @brief Used to check if the Node is a valid one that is whether it is in the grid or not
 *
 * @param curr is of type Node
 * @return bool true if the node's x and y values are in the limits of the grid
 */
bool Grid::isValid(Node curr){

	return ((curr._x<_columns)&&(curr._y<_rows)&&(curr._y>=0)&&(grid[curr._y][curr._x]))?true:false;

}
/**
 * @brief A friend of the class Grid. Overloads the ostream opertor << ,used to display the map
 *
 * @param out is a reference of an ostream object
 * @param g is a reference of a Grid object
 * @return overloads the << operator
 */
std::ostream & operator<<(std::ostream & out, Grid & g)
{

    for(int i=0;i<g._rows;++i)
    {
        for(int j=0;j<g._columns;++j)
        {
      if (g.start == Node(j, i)) {
        g.grid[i][j] = 's';
        out << 's';  //prints s if start node
      }
      if (g.goal == Node(j, i)) {
        g.grid[i][j] = 'g';

        out << 'g';  //prints g if goal node
      }
      if (g.grid[i][j] == 'o')
        out << 'o';  //prints o for obstacle
      if (g.grid[i][j] == 'x')
        out << 'x';  //prints x for the path
      if (g.grid[i][j] == 'u')
        out << 'u';  //prints u for the unexplored nodes in the grid
    }
    out << std::endl;
    }
    return out;
}

Grid::~Grid() {
}

