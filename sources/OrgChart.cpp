#include "OrgChart.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include<algorithm>
using namespace std;
using namespace ariel;


OrgChart::OrgChart(){ //init empty tree
    this->first = nullptr;
}

OrgChart::~OrgChart(){ //delete tree to avoid memory leaks
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
    if(this->first != nullptr){ //in case we add root in the middle of adding subs we replace the root and take all its children
       Node *root = newNode(position);
       root->subs = this->first->subs;
       this->first = root;
    }else{ // if not we just add it
        this->first = newNode(position);
    }
    
    return *this; //add new node as the root
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
// vector<Node*> toDeleteList; 
//  queue<Node *> q; 
//     q.push(root); 
//     while (!q.empty()){
//         int n = q.size();
//         while (n > 0){
//             Node * p = q.front();
//             q.pop();
//             toDeleteList.push_back(p);
//             for (int i = 0; i < p->subs.size(); i++){
//                 q.push(p->subs.at((unsigned long)i));
//             }
//             n--;
//         }
//     }
//      for (int i = 0; i < toDeleteList.size(); i++){
//             delete(toDeleteList.at((unsigned long)i));
// }
    delete(root);
}

// int main(){
//     class Person {
//     public:
//         string name;
//         int age;

//         Person(string Name, int Age) : name(Name), age(Age) {}

//         bool operator==(Person &p1) {
//             return this->name == p1.name;
//         }
//     };
//     //instantiate People
//     Person Great_GrandFather("Great_GrandFather", 85);
//     Person Grandfather("GrandFather", 65);
//     Person Father("Father", 45);
//     Person Uncle("Uncle", 43);
//     Person Aunt("Aunt", 43);
//     Person Son("Son", 20);
//     Person Daughter("Daughter", 18);
//     Person Cousin("Cousin", 15);

//     OrgChart chart1;
//             (chart1.add_root(Aunt.name));
//             (chart1.add_root(Great_GrandFather.name));
//             (chart1.add_sub(Great_GrandFather.name, Grandfather.name));
//             (chart1.add_sub(Grandfather.name, Father.name));
//             (chart1.add_sub(Grandfather.name, Uncle.name));
//             (chart1.add_sub(Grandfather.name, Aunt.name));
//             (chart1.add_sub(Father.name, Son.name));
//             (chart1.add_sub(Father.name, Daughter.name));
//             (chart1.add_sub(Uncle.name, Cousin.name));
//              Person Cousin2("Cousin2", 14);
//                  Person GreatUncle("GreatUncle", 62);
//                (chart1.add_sub(Aunt.name, Cousin2.name));
//                            (chart1.add_sub(Great_GrandFather.name, GreatUncle.name));
//                  Person GreatGrandma("GreatGrandma", 84);
//             (chart1.add_root(GreatGrandma.name));

//                 vector<string> pre_order;
//             for (auto it = chart1.begin_preorder(); it != chart1.end_preorder(); ++it) {
//                 cout << *it << " ";
//     }
  
// }
 
