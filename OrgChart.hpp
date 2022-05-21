#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
namespace ariel{
    class OrgChart{
       private:
      
        
        public:
         struct Node{
            string data;
            vector<Node *> subs;

        };
        Node *newNode(string data){
        Node *temp = new Node;
        temp->data = data;
        return temp;
        }
        Node *first;
        OrgChart();
        ~OrgChart();
        OrgChart& add_root(string position);
        OrgChart& add_sub(string higherPosName, string lowerPosName);
        friend ostream& operator<<(ostream& output, const OrgChart &org);
        Node* getNode(string name);
    class Iterator{
      private:
      int curr_index; //get node at this index
      vector<Node*> tree_list; //list of traversal
      public:

    void level_order(Node* root){
    queue<Node *> q; 
    q.push(root); 
    while (!q.empty()){
        int n = q.size();
        while (n > 0){
            Node * p = q.front();
            q.pop();
            this->tree_list.push_back(p);
            for (int i = 0; i < p->subs.size(); i++){
                q.push(p->subs.at(i));
            }
            n--;
        }
    }
}
    void reverse_order(Node* root){
        queue<Node *> q; //init q
        stack<Node *> s; // init stack
        q.push(root); 
        while(!q.empty()){
            Node *n = q.front(); //get the first in order
            q.pop();
            s.push(n); //insert the next one from last
            for(int i = n->subs.size() - 1; i >= 0; i--){ //iterate over children
                q.push(n->subs.at(i));
            }
        }
        while(!s.empty()){
            this->tree_list.push_back(s.top()); //add to final list
            s.pop();
        }
    }


      void preorder(Node *root){
        stack<Node*> s; //init stack
        s.push(root); 
        while (!s.empty()) {
        Node* temp = s.top(); //get always the top
        s.pop(); 
        this->tree_list.push_back(temp); //push it to final result
        for (int i = temp->subs.size() - 1; i >= 0; i--) { //iterate over children
            s.push(temp->subs.at(i));
        }
        }
}

      Iterator(Node* ptr, int traverse_way){
          if(traverse_way == 0 && ptr != nullptr){ //if 0 and we are not at the end begin level order
              level_order(ptr);
          }else if(traverse_way == 1 && ptr != nullptr){//if 1 and we are not at the end begin reverse order
              reverse_order(ptr);
          }else{
              if(ptr != nullptr){//if 2 and we are not at the end begin preorder
                  preorder(ptr);
              }
          }
          this->curr_index = 0;
          this->tree_list.push_back(nullptr);
      }
      bool operator!=(const Iterator& it) const{
            return this->tree_list[this->curr_index] != it.tree_list[it.curr_index];
    }
        
     const Iterator operator++(int){
         Iterator t = *this; //save as temp because we firse return and then add
         this->curr_index++;
          return t;
      }
      Iterator& operator++(){
          ++this->curr_index; //add then return
          return *this;
      }
      string operator*() const{
          return this->tree_list[curr_index]->data;
      }
      string* operator->() const{
          return &(this->tree_list[curr_index]->data);
      }

    // bool operator==(const Iterator &it) const {
    //         return !(*this != it);
    //     }

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