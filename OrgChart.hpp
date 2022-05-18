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
    class Iterator{
      private:
      int curr_index;
      vector<Node*> tree_list;
      public:

    void level_order(Node* root){
    queue<Node *> q; // Create a queue
    q.push(root); // Enqueue root
    while (!q.empty())
    {
        int n = q.size();

        while (n > 0)
        {
            Node * p = q.front();
            q.pop();
            this->tree_list.push_back(p);
            for (int i=0; i<p->subs.size(); i++){
                q.push(p->subs.at(i));
            }
            n--;
        }
    }  
}

      void reverse_order(Node *root){

      }

      void preorder(Node *root){
        stack<Node*> s;
        vector<string> orderNodes;
        s.push(root);
        while (!s.empty()) {
        Node* temp = s.top();
        s.pop();
        // store the key in preorder vector(visited list)
        this->tree_list.push_back(temp);
        // Push all of the child nodes of temp into
        // the stack from right to left.
        for (int i = temp->subs.size() - 1; i >= 0; i--) {
            s.push(temp->subs.at(i));
        }
        }
}

      Iterator(Node* ptr, int traverse_way){
          if(traverse_way == 0 && ptr != nullptr){
              level_order(ptr);
          }else if(traverse_way == 1 && ptr != nullptr){
              reverse_order(ptr);
          }else{
              if(ptr != nullptr){
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
         Iterator t = *this;
         this->curr_index++;
          return t;
      }
      Iterator& operator++(){
          ++this->curr_index;
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