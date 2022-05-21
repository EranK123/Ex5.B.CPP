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

//uses level order to find the node with the matching name
OrgChart::Node* OrgChart::getNode(string name){
    if(this->first == nullptr){
        throw std::invalid_argument("Need to add root first");
    }
    queue<Node *> q; 
    q.push(this->first); 
    while (!q.empty()){
        int n = q.size();
        while (n > 0){
            Node * p = q.front();
            q.pop();
            if(p->data == name){
                return p;
            }
            for (int i = 0; i < p->subs.size(); i++){
                q.push(p->subs.at(i));
            }
            n--;
        }
    }
    return nullptr;
}

OrgChart& OrgChart::add_root(string position){
    if(position == "\n" || position == "\t" || this->first != nullptr){
        throw std::invalid_argument("Cant accept these strings");
    }
    this->first = newNode(position); //add new node as the root
    return *this;
}

OrgChart& OrgChart::add_sub(string higherPosName, string lowerPosName){
    if(higherPosName == "\n" || higherPosName == "\t" || lowerPosName == "\n" || lowerPosName == "\t"){ //bad strings
        throw std::invalid_argument("Cant accept these strings");
    }
  
    Node *new_node = newNode(lowerPosName); //create new node
    Node* higher = getNode(higherPosName); //get the node with the higher position name
    if(higher == nullptr){ //if its null throw 
        throw std::invalid_argument("Cant sub to Null");
    }
    higher->subs.push_back(new_node); //push lower node to higher node
    return *this;
    }
//uses level order to output all nodes
ostream& ariel::operator<<(ostream& output, const OrgChart &org){
	queue<OrgChart::Node *> q;  //init q
	q.push(org.first); 
	while (!q.empty()){
		int n = q.size();

		while (n > 0){
			OrgChart::Node * p = q.front();
			q.pop();
			output << p->data << " ";
			for (int i = 0; i < p->subs.size(); i++){
				q.push(p->subs.at(i));
            }
			n--;
		}
		output << endl; 
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
    return Iterator(this->first , 1);
}
OrgChart::Iterator OrgChart::reverse_order(){
    return Iterator(nullptr, 1);
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
      .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
      .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
      .add_sub("COO", "VP_BI")
      .add_sub("VP_SW", "Rookie"); 
    for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it)
  {
    cout << (*it) << " " ;

  }
}
 
