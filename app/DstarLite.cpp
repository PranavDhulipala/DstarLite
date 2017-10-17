
#include "DstarLite.h"



double DstarLite::distance(Node n1, Node n2) {
  return ((sqrt(pow(n2._x - n1._x, 2) + pow(n2._y - n1._y, 2)))
      * (rand() % 10 + 1));
 }

double DstarLite::heuristic(Node n, Grid g) {
  return (sqrt(pow(n._x - g.start._x, 2) + pow(n._y - g.start._y, 2)));
}

void DstarLite::initialize(Grid &grid, std::vector<std::vector<double> > &g,
                           std::vector<std::vector<double> > &rhs, int km) {

  rhs[grid.goal._y][grid.goal._x] = 0;  
  std::pair<double, double> k = calculateKey(grid, grid.goal, g, rhs, km);  
  grid.goal.setkey(k);  
  U.push(grid.goal);  

}



std::vector<Node> DstarLite::getNeighbours(Grid &grid,Node &node){
  std::vector<Node> neighbours;  
  std::vector<int> xVal = { -1, -1, -1, 0, 0, 1, 1, 1 };  
  std::vector<int> yVal = { -1, 0, 1, -1, 1, -1, 0, 1 };  

  for (size_t i = 0; i < xVal.size(); i++) {
    Node n(node._x + xVal[i], node._y + yVal[i]);
    if (grid.isValid(n)) {
      neighbours.push_back(n);  
    }
  }
  return neighbours;  
}

std::pair<double, double> DstarLite::calculateKey(
    Grid &grid,
    Node &node, std::vector<std::vector<double> > &g,
    std::vector<std::vector<double> > &rhs, int km) {

  double minVal =
      g[node._y][node._x] > rhs[node._y][node._x] ?
          rhs[node._y][node._x] : g[node._y][node._x];  
  double key1 = minVal + heuristic(node, grid) + km;
  double key2 = minVal;

  return std::make_pair(key1, key2);  
}




void DstarLite::updateVertex(Node &u, std::vector<std::vector<double> > &g,
                             std::vector<std::vector<double> > &rhs,
                             std::vector<std::vector<double> > &cost,
                             Grid &grid, int km) {
	if(u!=grid.goal){
    std::vector<Node> neighbourList = getNeighbours(grid, u);  
    std::vector<double> valUpdate;

	 for(auto n:neighbourList){
      valUpdate.push_back(g[n._y][n._x] + cost[n._y][n._x]);  
	 }
    rhs[u._y][u._x] = *std::min_element(valUpdate.begin(), valUpdate.end());  

	}

	if(u==U.find(u)){
    U.remove(u);  
	 }
  if (g[u._y][u._x] != rhs[u._y][u._x]) {
    auto key = calculateKey(grid, u, g, rhs, km);  
    u.setkey(key);  
    U.push(u);  
	}

}



void DstarLite::computePath(Grid & grid, std::vector<std::vector<double> > &g,
                            std::vector<std::vector<double> > &rhs,
                            std::vector<std::vector<double> > &cost, int km) {




  while (U.top() < calculateKey(grid, grid.start, g, rhs, km)
      || (rhs[grid.start._y][grid.start._x] != g[grid.start._y][grid.start._x])) {

    Node u = U.top();  
    U.pop(); 
    if (u < calculateKey(grid, u, g, rhs, km)) {
      std::pair<double, double> knew = calculateKey(grid, u, g, rhs, km);
    		u.setkey(knew);
    		U.push(u);
    	}
    
    	else if (g[u._y][u._x] > rhs[u._y][u._x]) {
      g[u._y][u._x] = rhs[u._y][u._x]; 
    	    std::vector<Node> neighbours = getNeighbours(grid,u);
    	        for(auto &n:neighbours){
        if (cost[n._x][n._y] == 1)
          updateVertex(n, g, rhs, cost, grid, km);  
    	        }
    	}
    	else{
      g[u._y][u._x] = grid._columns * grid._rows + 1;  
    		std::vector<Node> neighbours = getNeighbours(grid,u);
      for (auto &n : neighbours) {
        if (cost[n._x][n._y] == 1)  
          updateVertex(n, g, rhs, cost, grid, km);  
      }
      updateVertex(u, g, rhs, cost, grid, km);  
    }
    	}



}


std::vector<Node> DstarLite::scan(Grid &grid, Node &curr,
                                  std::vector<std::vector<double> > &cost,
                                  int scanRange) {


    std::vector<Node> newSet;

 
  int rangeChecked = 0;

  std::vector<Node> statestoUpdate = getNeighbours(grid, curr);
  rangeChecked = 1;

  while (rangeChecked < scanRange) {

    for (auto state : statestoUpdate) {

      newSet.push_back(state);


      std::vector<Node> n = getNeighbours(grid, state);
      for (auto n1 : n) {
        
        if ((grid.grid[n1._y][n1._x] == 'o')) {
          cost[n1._y][n1._x] = grid._columns * grid._rows + 1;  
          
          newSet.erase(
              std::remove_if(newSet.begin(), newSet.end(), [&](const Node& x) {

                return x == n1;
              }),
              newSet.end());

          newSet.push_back(n1);
        } else
          continue;
      }
    }
    rangeChecked += 1;
    statestoUpdate = newSet;

  }

  return statestoUpdate;
}
