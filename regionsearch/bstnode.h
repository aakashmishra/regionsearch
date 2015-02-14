//
//  bstnode.h
//  regionsearch
//
//  Created by Aakash Anand Mishra on 11/10/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//

#ifndef regionsearch_bstnode_h
#define regionsearch_bstnode_h

using namespace std;
class bstnode{
public:
    int x;
    int y;
    string name;
    bstnode* left;
    bstnode* right;
    bstnode* copy;
    bstnode(){
        x=0;
        y=0;
        name ="";
        left= NULL;
        right = NULL;
        copy =NULL;
        
    }
    bstnode(int x_co,int y_co,string cityname){
        x= x_co;
        y= y_co;
        name = cityname;
        left =NULL;
        right = NULL;
        copy =NULL;
    }
};
#endif