//
//  binarytree.h
//  regionsearch
//
//  Created by Aakash Anand Mishra on 11/5/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//

#ifndef __regionsearch__binarytree__
#define __regionsearch__binarytree__

#include <stdio.h>
#include <iostream>
#include "bstnode.h"
using namespace std;


 /* defined(__regionsearch__binarytree__) */

class Binarytree
{
    
public:
    bstnode* rootptr;  //binary pointer is defined
    bstnode* rootptr1; // binary pointer is defined
    Binarytree(){
        rootptr = NULL; //constructor
    }
    
    
    void makenull(){     // to make null constructor is used
        Binarytree();
    }
    
    int Empty(){       // to check if the binary tree is empty
        if (rootptr == NULL){
            return 1;
            }
        else{
            return 0;
        }
    }
    void insert(int x, int y,string cityname){
        if ((x < 0) or (x>16384) or (y<0) or (y>16384)){   // to check for the validity of the input
            cout<<"invalid data"<<endl;
            return;
        }

        if (rootptr == NULL){
            rootptr = new bstnode(x,y,cityname);  // making a new node incase the pointer is empty
        }
        else{
            insert(rootptr,x,y,cityname);  //calling the insert function
        }
    }
    
void insert (bstnode* node,int x,int y, string cityname){
    if ((x < 0) or (x>16384) or (y<0) or (y>16384)){  // to check for the validity of the input
        cout<<"invalid data"<<endl;
        return;
    }
        if (node == NULL){
            //cout<<"null";
            
            node = new bstnode(x,y,cityname);  //if node is null the value is inserted at the node
            return;
        }
        else if(cityname <node->name){   // the name of the city is compared to the name of the node and accordingly passed to the right or left pointers
            if(node->left!= NULL){
          
            insert(node->left,x,y,cityname);// recursive call is made inorder to reach a null pointer to insert data
            }
            else{
            bstnode* node1 =new bstnode(x,y,cityname); // if null then data is inserted
                node->left = node1;
            }
        
        }
        else if(cityname > node->name){// the name of the city is compared to the name of the node and accordingly passed to the right or left pointers
            
            if(node->right!= NULL){
        insert(node->right,x,y,cityname); // recursive call is made inorder to reach a null pointer to insert data
            }
            else{
                
            bstnode* node1 =new bstnode(x,y,cityname); // if null then data is inserted
                node->right = node1;
                
            }

        }
        else if(cityname == node->name){  // to insert duplicate records
            while (node->copy != NULL){
                node = node->copy;
            }
            bstnode* duplicate = new bstnode(x,y,cityname);
            node -> copy = duplicate;
            
            
        }
   
        }
        
bstnode* search(bstnode* node,string name){ // search the cityname and print its coordinates
   
        if (node == NULL){
            cout<< "data not found"<<endl;
            return 0;
        }
        else if(name == node->name){ // if leaf is equal to the name passed print its coordinates
            if(node -> copy == NULL){
                cout<<" cityname "<<node->name<<" x coordinate "<<node->x<<" y coordinate "<<node->y<<endl;
            }
            if (node ->copy != NULL){
            while (node-> copy != NULL){
                cout<<" cityname "<<node->name<<" x coordinate "<<node->x<<" y coordinate "<<node->y<<endl;

                node =node -> copy;
            }
                cout<<" cityname "<<node->name<<" x coordinate "<<node->x<<" y coordinate "<<node->y<<endl;
              
            }
            return node;
            }
        else if(name < node->name){ //recursion used to go to the left
            return search(node->left,name);
        }
        else {    //recursion used to go to the right
            return search(node->right,name);
        }
        
};
    bstnode* findmin(bstnode* node){ //findmin is used to go to the smallest node
        
        if (node == NULL){
            return NULL;
        }
        if (node -> left == NULL){
            return node;
         }
        return findmin(node->left);
        }
    void remove(string name){
                if (Empty()){
            cout<<"no nodes";
        
        remove(rootptr,name,rootptr1);
    }
    }
    void remove(bstnode* node,string name,bstnode* prepointer){
        
    
        if (node ==NULL){
            cout << "no data found"<<endl;  // if data is not found
            return;
        }
        if (name < node->name){
            remove(node->left,name,node); // traverse left if name<node->name
            }
        if (name > node->name){
            remove(node->right,name,node);// traverse right if name>node->name
        }
        if (name == node->name){
         /*incase both the nodes are not empty the value of the samllest node in the right subtree is replaced
          */
            if (node->left!= NULL && node->right!= NULL){
                node -> name = (findmin(node->right)->name);
                node -> x = (findmin(node->right)->x);
                node -> y = (findmin(node->right)->y);
                node -> copy = (findmin(node->right)->copy);
                remove(node->right,node->name,node);
            }
            /*
             else the parent of the node is updated with the value of its child if only one node exists and then the node is deleted
             */
            else{
            
                if(prepointer->name>node->name){
                    
               
                if (node->left!= NULL) {
                    
                    prepointer->left =node->left;
                }
                else if(node->right!= NULL){
                    prepointer->left = node->right;
                }
                }
                else if(prepointer->name<node->name){
                    if (node->left!= NULL) {
                        prepointer->right =node->left;
                    }
                    else if(node->right!= NULL){
                        prepointer->right = node->right;
                    }
                }
                else{
                
                    prepointer->left = NULL;
                    prepointer->right= NULL;
                }
                

                
                bstnode* a =node;
                delete a;

            }
            
            
            
            
        }
    }
    

    

};
#endif


