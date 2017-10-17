
#ifndef APP_DSTARLITE_H_
#define APP_DSTARLITE_H_
#include "Node.h"
#include "Grid.h"
#include <algorithm>
#include "PriorityQ.h"
#include <cmath>


class DstarLite {
public:


  double distance(Node n1, Node n2);

  double heuristic(Node n, Grid g);

  void initialize(Grid &grid, std::vector<std::vector<double> > &g,
                  std::vector<std::vector<double> > &rhs, int km);


  std::vector<Node> getNeighbours(Grid &grid, Node &node);

  std::pair<double, double> calculateKey(Grid &grid, Node &node,
                                         std::vector<std::vector<double> > &g,
                                         std::vector<std::vector<double> > &rhs,
                                         int km);


  void updateVertex(Node &u, std::vector<std::vector<double> > &g,
                    std::vector<std::vector<double> > &rhs,
                    std::vector<std::vector<double> > &cost, Grid &grid,
                    int km);


  void computePath(Grid & grid, std::vector<std::vector<double> > &g,
                   std::vector<std::vector<double> > &rhs,
                   std::vector<std::vector<double> > &cost, int km);

  
  PriorityQ<Node> U;

  std::vector<Node> scan(Grid &grid, Node &curr,
                         std::vector<std::vector<double> > &cost,
                         int scanRange);

};
#endif /* APP_DSTARLITE_H_ */


