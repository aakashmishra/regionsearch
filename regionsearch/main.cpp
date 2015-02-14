//
//  main.cpp
//  regionsearch
//
//  Created by Aakash Anand Mishra on 11/5/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//
#include "binarytree.h"
#include "quadtree.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <vector>
#include "internalnode.h"
using namespace std;
prquadtree q;
Binarytree b;

void output(vector<string> input)
    {
        string word = input[0]; //The first input is taken into word
        
        
        if (word == "insert") // checked for insert
        {
           
            int x = atoi(input[1].c_str());//to get x coordinate
            int y = atoi(input[2].c_str());//to get y coordinate
            string name = input[3];// //to get name of the city
            q.insert(q.root, x, y, name);//insert in quadtree
            b.insert(x,y,name);//insert in binarytree
        }
        
       
        if (word == "makenull")//makenull makes both trees makenull
        {
            q.makenull();
            b.makenull();
        }
        
       
        if (word == "find")
        {
            
            string name = input[1];
           
            b.search(b.rootptr,name);// to search coordinates of a city
            
             
        }
        
       
        if (word == "debug")
        {
            q.debug(q.root);// to show the coordinates and the city
            cout<<'\n';
        }
        
     
        if (word == "search")
        {
            int x = atoi(input[1].c_str());
            int y = atoi(input[2].c_str());
            int r = atoi(input[3].c_str());
            q.search(q.root,x, y, r);// to search within a radius
        }
        
       
        /* remove function will have two cases 
         1. to remove by using name
           the coordinates of the name are found using the node from the output of the search function in the binary tree
           these coordinates are then used to delete from the quadtree
         2.to remove using the coordinates
           the name is received using the find function
           this name is then used to delete from the binary tree
         */
         if (word == "remove")
        {
            bstnode* node;
           
            if (input.size() == 3){
               
                string name =input[1];
                cout<<name;
                node = b.search(b.rootptr, name);
                
                
            if (node == NULL)
            {
                cout<<"there is no node in BST.(remove)"<<endl;
            }
            else
            {
                if (node->copy == NULL)
                    { cout<<node->name<<" x "<<node->x<<" y "<<node->y<<" is to be deleted"<<endl;
                        q.remove(q.root,node->x, node->y,q.root);
                }
                else
                {
                    while(node->copy!=NULL)
                    {
                        cout<<"remove: "<<node->name<<"("<<node->x<<", "<<node->y<<")"<<endl;
        q.remove(q.root,node->x, node->y,q.root);
                        node = node->copy;
                    }
                    b.remove(name);
                }
            }
            }
            else{
               
            
                int x = atoi(input[1].c_str());
                int y = atoi(input[2].c_str());
                string z ;
        
                q.find(q.root,x,y,z);
                
                
                if (z != "no"){
                q.remove(q.root,x,y,q.root);
                b.remove(z);
                }
                else{
                    cout << " no element deleted "<<endl;
                }
                
                
            }
    }
    }
    
    int main(int argc, char *argv[])


{
    /* A vector of string arguments is used here in order to get the input names from the file
      These inputs are then used accordingly in the output function
     */
        string input;
        vector<string> commandLine;
        ifstream commandfile;
        commandfile.open(argv[1]);
    
        while (getline(commandfile, input))
        {
            istringstream istr(input);
            while( !istr.eof() )
            {
                string tmp_s;
                istr >> tmp_s;
                commandLine.push_back(tmp_s);
            }
            output(commandLine);
            commandLine.clear();
        }
      
    }
    
