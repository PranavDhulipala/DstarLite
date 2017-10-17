
#ifndef APP_NODE_H_
#define APP_NODE_H_


#include <utility>
#include <iostream>


class Node {
 public:

	int _x=0;
int _y=0;

	std::pair<double, double> _key=std::make_pair(0,0);

	Node();

  Node(int x, int y);

  Node(const Node& n);

  void setkey(std::pair<double, double> &k);

	std::pair<double, double> getkey();

  friend const Node operator+(const Node &l, const Node &r);

  friend bool operator==(const Node &l, const Node &r);

  friend bool operator!=(const Node &l, const Node &r);

  friend std::ostream & operator<<(std::ostream &,Node &);
 
	friend bool operator<(const Node& l,const std::pair<double,double> r){
		        if(l._key.first<r.first)
		            return true;
		        else
		        {
		            if ((l._key.first==r.first)&&(l._key.second<r.second))
		                return true;
		            else
		                return false;
		        }
	}
 
	~Node();
};


#endif /* APP_NODE_H_ */
