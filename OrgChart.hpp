#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
namespace ariel{
    class OrgChart{
        private:
       struct Node{
            string position;
            // vector<string> s;
            Node *next;
            Node(const string &pos, Node* n){
                position = pos;
                next = n;
            }
        };
        
        public:
        OrgChart();
        OrgChart& add_root(string position);
        OrgChart& add_sub(string higherPosName, string lowerPosName);
        friend ostream& operator<<(ostream& output, const OrgChart &org);
    class Iterator{
      private:
      uint index;
      Node *currentNode;
      public:
      Iterator(){
          this->index = 0;
          this->currentNode = NULL;
      }
    //   Iterator(Node* ptr = nullptr){
    //       this->currentNode = ptr;
    //   }
      bool operator!=(const Iterator& it) const{
          return false;
      }
     const Iterator operator++(int){
         Iterator t = *this;
          return t;
      }
      Iterator& operator++(){
          return *this;
      }
      string operator*() const{
          return "";
      }
      string* operator->() const{
          return nullptr;
      }

    };
    Iterator begin();
    Iterator end();
    Iterator begin_level_order();
    Iterator end_level_order();
    Iterator begin_reverse_order();
    Iterator reverse_order();
    Iterator begin_preorder();
    Iterator end_preorder();
 };
   
}