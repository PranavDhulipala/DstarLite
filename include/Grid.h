
#ifndef APP_GRID_H_
#define APP_GRID_H_

#include "Node.h"
#include<vector>
#include<queue>
#include<algorithm>


class Grid {
public:

  int _rows;

  int _columns;
  
	Node start;
  

  std::vector<std::vector<char>> grid;

 

  Grid(int rows, int columns);
  
  void obstacle(Node tl, Node br);  
  
  bool isValid(Node curr);
 

  friend std::ostream & operator<<(std::ostream & out, Grid &g);

	~Grid();
};



#endif /* APP_GRID_H_ */
