
#include "Node.h"

Node::Node() {

}

Node::Node(int x,int y): _x(x),_y(y){}

Node::Node(const Node &n){
	_x=n._x;
	_y=n._y;
	_key=n._key;
}

void Node::setkey(std::pair<double, double> &k){
	_key=k;
	}

std::pair<double,double> Node::getkey(){
	return _key;
}

const Node operator+(const Node &l,const Node &r){
	return Node(l._x+r._x,l._y+r._y);

}

bool operator==(const Node &l,const Node &r){
	return ((l._x == r._x)&&(l._y==r._y));
}

bool operator!=(const Node &l,const Node &r){
	return !(l==r);
}

std::ostream & operator<<(std::ostream &out,Node &n){
	out<<n._x<<n._y;
	return out;
 }

Node::~Node() {}


