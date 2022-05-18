#include "OrgChart.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include<algorithm>
using namespace std;
using namespace ariel;


OrgChart::OrgChart(){
    this->first = nullptr;
}

OrgChart::~OrgChart(){
    delete(this->first);
}

OrgChart& OrgChart::add_root(string position){
    this->first = newNode(position);
    return *this;
}

OrgChart& OrgChart::add_sub(string higherPosName, string lowerPosName){
    Node *new_node = newNode(lowerPosName); //create new node
    if(higherPosName == this->first->data){ //if its the root add it
    this->first->subs.push_back(new_node);   
    }
    Node *temp = this->first;
    for(size_t i = 0; i < temp->subs.size(); i++){
        if(temp->subs.at(i)->data == higherPosName){
            temp->subs.at(i)->subs.push_back(new_node);
            break;
        }  
    }
    return *this;
    }

ostream& ariel::operator<<(ostream& output, const OrgChart &org){
	queue<OrgChart::Node *> q; // Create a queue
	q.push(org.first); // Enqueue root
	while (!q.empty())
	{
		int n = q.size();

		// If this node has children
		while (n > 0)
		{
			// Dequeue an item from queue and print it
			OrgChart::Node * p = q.front();
			q.pop();
			output << p->data << " ";

			// Enqueue all children of the dequeued item
			for (int i=0; i<p->subs.size(); i++){
				q.push(p->subs.at(i));
            }
			n--;
		}

		output << endl; // Print new line between two levels
	}
    return output;
}

OrgChart::Iterator OrgChart::begin(){
    return Iterator(this->first, 0);
}
OrgChart::Iterator OrgChart::end(){
    return Iterator(nullptr, 0);
}
OrgChart::Iterator OrgChart::begin_level_order(){
    return Iterator(this->first, 0);
}
OrgChart::Iterator OrgChart::end_level_order(){
    return Iterator(nullptr, 0);
}
OrgChart::Iterator OrgChart::begin_reverse_order(){
    return Iterator(nullptr , 1);
}
OrgChart::Iterator OrgChart::reverse_order(){
    return Iterator(this->first, 1);
}
OrgChart::Iterator OrgChart::begin_preorder(){
    return Iterator(this->first, 2);
}
OrgChart::Iterator OrgChart::end_preorder(){
    return Iterator(nullptr, 2);
}

int main(){
    OrgChart org;
    org.add_root("CEO")
      .add_sub("CEO", "CTO")        // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")        // Now the CFO is subordinate to the CEO         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
      .add_sub("CEO", "COO")
        .add_sub("COO", "VP_BI");
    for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it)
  {
    cout << (*it) << " " ;
  }
// for (auto element : org)
//   { // this should work like level order
//     cout << element << " " ;
//   } // 
//    / prints: CEO CTO CFO COO VP_SW VP_BI
   
// cout << org;

}