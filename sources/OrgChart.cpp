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
			output << p->data << " ";
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
    return Iterator(this->first, 0);
}
OrgChart::Iterator OrgChart::end(){
    return Iterator(nullptr, 0);
}
OrgChart::Iterator OrgChart::begin_level_order() const{
    return Iterator(this->first, 0);
}
OrgChart::Iterator OrgChart::end_level_order(){
    return Iterator(nullptr, 0);
}
OrgChart::Iterator OrgChart::begin_reverse_order() const{
    return Iterator(this->first , 1);
}
OrgChart::Iterator OrgChart::reverse_order(){
    return Iterator(nullptr, 1);
}
OrgChart::Iterator OrgChart::begin_preorder() const{
    return Iterator(this->first, 2);
}
OrgChart::Iterator OrgChart::end_preorder(){
    return Iterator(nullptr, 2);
}

// int main(){
//      vector<string> names = {"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
//     vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
//     vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
//     vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
//     OrgChart organization;
//     organization.add_root(names[0])
//         .add_sub(names[0], names[1])  // Now the CTO is subordinate to the CEO
//         .add_sub(names[0], names[2])  // Now the CFO is subordinate to the CEO
//         .add_sub(names[0], names[3])  // Now the COO is subordinate to the CEO
//         .add_sub(names[1], names[4])  // Now the VP Software is subordinate to the CTO
//         .add_sub(names[3], names[5]); // Now the VP_BI is subordinate to the COO
//     //        CEO
//     //        |--------|--------|
//     //        CTO      CFO      COO
//     //        |                 |
//     //        VP_SW             VP_BI
//     //  */
//     size_t i = 0;
//     for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
//     {
//         cout << (*it) << " ";
//     } // Needs to be: CEO CTO CFO COO VP_SW VP_BI
//     cout << endl;
//     i = 0;
//     for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
//     {
//         cout << (*it) << endl;
//     } // Needs to be: VP_SW VP_BI CTO CFO COO CEO
//     i = 0;
//     for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
//     {
//         cout << (*it) << endl;
//     } // Needs to be: CEO CTO VP_SW CFO COO VP_BI
//     i = 0;
//     for (auto element : organization)
//     { // this should work like level order
//         cout << element << " ";
//     } // Needs to be: CEO CTO CFO COO VP_SW VP_BI
//     cout << endl;
//     i = 0;
//     // demonstrate the arrow operator:
//     for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
//     {
//         cout << it->size() << " ";
//     }// Needs to be: 3 3 3 3 5 5
// }
 
