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
    deleteOrg(this->first);
}

//uses level order to find the node with the matching name
OrgChart::Node* OrgChart::getNode(const string &name) const{
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
            for (unsigned long i = 0; i < p->subs.size(); i++){
                q.push(p->subs.at(i));
            }
            n--;
        }
    }
    return nullptr;
}

OrgChart& OrgChart::add_root(const string &position){
    if(position == "\n" || position == "\t"){
        throw std::invalid_argument("Cant accept these strings");
    }
    this->first = newNode(position); //add new node as the root
    return *this;
}

OrgChart& OrgChart::add_sub(const string &higherPosName, const string &lowerPosName){
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
			output << p->data << " "; //prints in level order matter
			for (unsigned long i = 0; i < p->subs.size(); i++){
				q.push(p->subs.at(i));
            }
			n--;
		}
		output << endl; 
	}
    return output;
}

OrgChart::Iterator OrgChart::begin() const{
    if(this->first == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    return Iterator(this->first, 0);
}
OrgChart::Iterator OrgChart::end() const{
    if(this->first == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    return Iterator(nullptr, 0);
}
OrgChart::Iterator OrgChart::begin_level_order() const{
    if(this->first == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    return Iterator(this->first, 0);
}
OrgChart::Iterator OrgChart::end_level_order() const{
      if(this->first == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    return Iterator(nullptr, 0);
}
OrgChart::Iterator OrgChart::begin_reverse_order() const{
    if(this->first == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    return Iterator(this->first , 1);
}
OrgChart::Iterator OrgChart::reverse_order() const{
    if(this->first == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    return Iterator(nullptr, 1);
}
OrgChart::Iterator OrgChart::begin_preorder() const{
    if(this->first == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    return Iterator(this->first, 2);
}
OrgChart::Iterator OrgChart::end_preorder() const{
    if(this->first == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    return Iterator(nullptr, 2);
}

void OrgChart::deleteOrg(Node *root){
//    queue<Node *> q; //init q
//         stack<Node *> s; // init stack
//         q.push(root); 
//         while(!q.empty()){
//             Node *n = q.front(); //get the first in order
//             q.pop();
//             s.push(n); //insert the next one from last
//             for(int i = n->subs.size() - 1; i >= 0; i--){ //iterate over children
//                 q.push(n->subs.at((unsigned long)i));
//             }
//         }
//         while(!s.empty()){
//             Node *t = s.top(); 
//             s.pop();
//             delete(t);
//         }
//         delete(root);
delete(this->first);
}

// int main(){
//   
// }
 
