

#include "Grid.h"

Grid::Grid(int rows, int columns)
    : _rows(rows),  
      _columns(columns),  
      start(-1, -1),  
      goal(-1, -1) {  
  grid.resize(rows, std::vector<char>(columns, 'u'));  
}


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



bool Grid::isValid(Node curr){

	return ((curr._x<_columns)&&(curr._y<_rows)&&(curr._y>=0)&&(grid[curr._y][curr._x]))?true:false;

}

std::ostream & operator<<(std::ostream & out, Grid & g)
{

    for(int i=0;i<g._rows;++i)
    {
        for(int j=0;j<g._columns;++j)
        {
      if (g.start == Node(j, i)) {
        g.grid[i][j] = 's';
        out << 's'; 
      }
      if (g.goal == Node(j, i)) {
        g.grid[i][j] = 'g';

        out << 'g';  
      }
      if (g.grid[i][j] == 'o')
        out << 'o'; 
      if (g.grid[i][j] == 'x')
        out << 'x';  
      if (g.grid[i][j] == 'u')
        out << 'u';  
    }
    out << std::endl;
    }
    return out;
}

Grid::~Grid() {
}

