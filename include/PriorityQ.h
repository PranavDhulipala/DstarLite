
#ifndef APP_PRIORITYQ_H_
#define APP_PRIORITYQ_H_
#include<queue>
#include<vector>
#include<algorithm>
#include"Node.h"


struct compare
{
bool operator()(Node &l, Node &r) {
	if(l._key.first<r._key.first)
    return false;
	else
     {
		if ((l._key.first==r._key.first)&&(l._key.second<r._key.second))
          return false;
		else
          return true;
     }
    }
};


template<typename T>
class PriorityQ : public std::priority_queue<T, std::vector<T>,compare>
{
  public:

	bool remove(const T& value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);  
	        if (it != this->c.end()) {
      this->c.erase(it);  
      std::make_heap(this->c.begin(), this->c.end(), this->comp);  
	            return true;
	       }
	       else {
	        return false;
	       }
	 }

  T find(const T& value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    return *it;

  }
};



#endif /* APP_PRIORITYQ_H_ */
