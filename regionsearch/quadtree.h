//
//  quadtree.h
//  regionsearch
//
//  Created by Aakash Anand Mishra on 11/5/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//

#ifndef __regionsearch__quadtree__
#define __regionsearch__quadtree__

#include <stdio.h>
#endif /* defined(__regionsearch__quadtree__) */
#include "binarytree.h"
#include "internalnode.h"
#include "leafnode.h"
#include <iostream>

class prquadtree{
private:
    int xmin,xmax,ymin,ymax;
public:
    internalnode* root;
    prquadtree(){    // constructor for prquadtree is defined
        xmax=16384; // 2^14 has been kept the maximum limit
        ymax=16384;
        xmin =0;
        ymin= 0;
        root = new internalnode();
        root->xcord= 16384/2;
        root->ycord= 16384/2;
        root->NW =NULL;
        root->SW = NULL;
        root->SE = NULL;
        root->NE = NULL;
        root->range = (xmax + xmin)/2;
        
        
    };
    
    void makenull(){                // makenull function make  everything null
        root->NW = NULL;
        root->NE = NULL;
        root->SW = NULL;
        root->SE = NULL;
       
    }
    bool isEmpty(){         // checks for empty prquadtree
        if(root->NW ==NULL && root->NE == NULL &&root->SW == NULL &&root->SE ==NULL){
            return true;
        }
        else{
                return false;
            }
        
    }
    
/* in this getinternalnode function the internal node is returned depending on its location from the current internal node passed as input
 */


internalnode* getinternalnode(internalnode* A,int x){
    internalnode* internal = new internalnode();
    if(x==1){
        internal->xcord = A->xcord - (A->range)/2;
        internal->ycord = A->ycord - (A->range)/2;
        
    }
    else if(x==2){
        internal->xcord = A->xcord + (A->range)/2;
        internal->ycord = A->ycord - (A->range)/2;
    }
    else if(x==3){
        internal->xcord = A->xcord - (A->range)/2;
        internal->ycord = A->ycord + (A->range)/2;
    }
    else if(x==4){
        internal->xcord = A->xcord + (A->range)/2;
        internal->ycord = A->ycord + (A->range)/2;
    }
    internal->range = (A->range)/2;   // range is always halved
    return internal;
    }
/*in the locate function an int value is returned depending on its location from the input internal node
  precaution has been taken that the node also take in the boundary conditions
 */
    
int locate(internalnode* p,int x, int y){
    //nw
    if (((x<= p->xcord) && (x>=p->xcord - p->range)) &&((y<p->ycord) && (y>=(p->ycord - p->range)))){
        return 1;
        }
    //ne
    else if (((x> p->xcord) && (x<=p->xcord + p->range)) &&((y<=p->ycord) && (y>=(p->ycord - p->range)))){
        return 2;
    }
    //sw
    else if (((x< p->xcord) && (x>=p->xcord - p->range)) &&((y>=p->ycord) && (y<=(p->ycord + p->range)))){
        return 3;
        }
    //se
    else {
        return 4;
        
    }
                                                           }
 /* the find function basically is used in order to change the contents of the string z to the name of the node having the x and y coordinates which is then used to remove the name from the binarytree
     This function uses recursive strategy to find the node having the x and y coordinates and changes the string z to either the name or 'no' depending on the coordinates*/

void find(nodequadbase* root,int x, int y,string &z){
   
    int l;
    if (isEmpty() == true){
        cout<<"empty quadtree";
        
    }
    else if (root->internal == false){
        
        if(root->xcord==x && root->ycord ==y){
           
            
            cout<<root->name<<" is to be deleted "<<" has coordinates "<<root->xcord<<" "<<root->ycord<<endl;
            z = root->name;
            
        }
        else{
            cout<<"data not found"<<endl;
            z = "no";
           
        }
        
    }
    else {
        internalnode* l1 = dynamic_cast<internalnode*>(root);
        l = locate(l1,x,y);
        
        if (l == 1){
            find(root->NW,x,y,z);
        }
        else if (l == 2){
            find(root->NE,x,y,z);
        }
        else if (l == 3){
            return find(root->SW,x,y,z);
        }

        else if (l == 4){
            return find(root->SE,x,y,z);
        }
     

    }
    
}
/*
 The search function is used in order to give all the citynames within the radius from a point
 recursive strategy is used here as well
 x^2 + y^2 = r^2 is the formula used here in order to calculate the city's that lie in the radius from the point x and y
 long ints have defined in order to check for overflow
 */
    
void search(nodequadbase* s, int x, int y, long radius){
    
        if (s== NULL){
            return;
        }
        else if (s->internal == true){
            search(s->NW,x,y,radius);
            search(s->NE,x,y,radius);
            search(s->SW,x,y,radius);
            search(s->SE,x,y,radius);
        }
        else{
            
            long int i = ((s->xcord - x)*(s->xcord - x));
            long int j = ((s->ycord - y)*(s->ycord - y));
            long int k = radius*radius;
        
            if((i + j) <= k){
                cout << "city name within the radius " <<" cityname "<<s->name<< " x "<<s->xcord<<" y "<<s->ycord << endl;
            }
            
                
            
        }
    }

void insert(nodequadbase* s, int x, int y, string name){
    
    if(x<0 or x>16384 or y<0 or y>16384){ // if the location is invalid
        cout<<"invalid location"<<x<<"  "<<y<<endl;
        return;
    }
    
    internalnode* l1 = dynamic_cast<internalnode*>(s);//dynamic casting is used in order to convert from base class to child class and vice versa
    int l = locate(l1,x,y);     // if the tree is empty
    if (isEmpty() == true){
        if(l==1){
            l1->NW = new leafnode(x,y,name);
        }
        if(l==2){
            l1->NE = new leafnode(x,y,name);
        }
        if(l==3){
            l1->SW = new leafnode(x,y,name);
        }
        if(l==4){
            l1->SE = new leafnode(x,y,name);
        }
     
    }
    /*
     each of the locations are checked for the particaular quadrant and then are passed accordingly in the following statements
     the following situations arrise
     1. if node is internal 
       i the particular quadrant is empty for example NW in l=1
       ii if already the same coordinates exists then msg is shown
       iii if the particular quadrant has an internalnode then recursion is used
       iv if already a leaf exists than new internal node is created and then the elements are inserted into that node
     */
    else{
        if (l==1){
       
            if(l1->internal==true){
                if(l1->NW == NULL){
                    l1->NW = new leafnode(x,y,name);
                }
                else if (l1->NW->xcord == x && l1->NW->ycord == y){
                    cout<<"location already exists"<<endl;
                }
                else if (l1->NW->internal == 1){
             
                    internalnode* l2 = dynamic_cast<internalnode*>(l1->NW);
                    insert(l2,x,y,name);
    
                }
                else
                {
                  
                    internalnode* l3 = getinternalnode(l1,l);
                    int x1 = l1->NW->xcord;
                    int y1 = l1->NW->ycord;
                    string name1 =l1->NW->name;
                    delete l1->NW;
                    l1->NW =l3;
                    
                    internalnode* l4 = dynamic_cast<internalnode*>(l3);
                    insert(l4,x1,y1,name1);
                    insert(l4,x,y,name);
                    
                }
            }
        }
        if (l==2){
            if(l1->internal==true){
                if(l1->NE == NULL){
                    l1->NE = new leafnode(x,y,name);
                }
                else if (l1->NE->xcord == x && l1->NE->ycord == y){
                    cout<<"location already exists";
                }
                else if (l1->NE->internal == 1){
                    internalnode* l2 = dynamic_cast<internalnode*>(l1->NE);
                    insert(l2,x,y,name);
                    
                }
                else{
                    internalnode* l3 = getinternalnode(l1,l);
                    int x1 = l1->NE->xcord;
                    int y1 = l1->NE->ycord;
                    string name1 =l1->NE->name;
                    delete l1->NE;
                    l1->NE =l3;
                    internalnode* l4 = dynamic_cast<internalnode*>(l3);
                    insert(l4,x1,y1,name1);
                    insert(l4,x,y,name);

                }
            }
        }
        if(l==3){
        if(l1->internal==true){
            if(l1->SW == NULL){
                l1->SW = new leafnode(x,y,name);
            }
            else if (l1->SW->xcord == x && l1->SW->ycord == y){
                cout<<"location already exists";
            }
            else if (l1->SW->internal == 1){
                internalnode* l2 = dynamic_cast<internalnode*>(l1->SE);
                insert(l2,x,y,name);
                
            }
            else{
                internalnode* l3 = getinternalnode(l1,l);
                int x1 = l1->SW->xcord;
                int y1 = l1->SW->ycord;
                string name1 =l1->SW->name;
                delete l1->SW;
                l1->SW =l3;
                internalnode* l4 = dynamic_cast<internalnode*>(l3);//diff
                insert(l4,x1,y1,name1);
                insert(l4,x,y,name);

                }
            }
        }
        if (l==4){
            if(l1->internal==true){
                if(l1->SE == NULL){
                    l1->SE = new leafnode(x,y,name);
                }
                else if (l1->SE->xcord == x && l1->SE->ycord == y){
                    cout<<"location already exists";
                }
                else if (l1->SE->internal == 1){
                    internalnode* l2 = dynamic_cast<internalnode*>(l1);
                    insert(l2,x,y,name);
                    
                }
                else{
                    internalnode* l3 = getinternalnode(l1,l);
                    int x1 = l1->SE->xcord;
                    int y1 = l1->SE->ycord;
                    string name1 =l1->SE->name;
                    delete l1->SE;
                    l1->SE =l3;
                    internalnode* l4 = dynamic_cast<internalnode*>(l3);//diff
                    insert(l4,x1,y1,name1);
                    insert(l4,x,y,name);

                }
            }
        }

    }
}
    
    void remove(nodequadbase* a,int x,int y,nodequadbase* prepointer){
       
        if(x<0 or x>16384 or y<0 or y>16384){//check for validity of the range
            cout<<"invalid location"<<endl;
            return;
        }
        
        if (isEmpty() == true){                         //if node is empty
            cout<<"NO element present";
            return;
        }
        if (a->internal ==1){
            internalnode* pre = dynamic_cast<internalnode*>(prepointer);// if node is internal
            internalnode* l1 = dynamic_cast<internalnode*>(a);
            int loc = locate(pre,l1->xcord,l1->ycord);
            int l = locate(l1,x,y);
          
            /*
             the different locations with respect to the internal nodes are identified and dealth accordingly in order to search for the node to be deleted
             different conditions that occur:
             i. if the link points to an internal node
                in that case recursion is used in order to go into the 
                internal node
             ii. if the link is a leaf
                1.the element is deleted
                2. it is checked for no of children left
                  if one child is left and is internal : it is left as it was
                  if one child is left and is leaf: the internal node is deleted and the pointer of the parent node is to be pointed at the leaf node
             
            */
            //nw
            if (l == 1){
                 // to check the location
                if (l1->NW->internal == true){
                    remove(l1->NW,x,y,l1);
                }
                if(l1->NW->internal ==false){
                    
                    if (l1->NW->xcord == x && l1->NW->ycord == y){
                        delete l1->NW;
                        l1->NW = NULL;
                     // to check for one child
                    if ((l1->NW!=NULL && l1->NE==NULL && l1->SW==NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE!=NULL && l1->SW==NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE==NULL && l1->SW!=NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE==NULL && l1->SW==NULL && l1->SE!=NULL) ){
                     
                       
                        if(l1->NW!=NULL && l1->NE==NULL && l1->SW==NULL && l1->SE==NULL && l1->NW->internal ==true){
                            return;
                        }
                        if(l1->NW==NULL && l1->NE!=NULL && l1->SW==NULL && l1->SE==NULL && l1->NE->internal ==true){
                            return;
                        }
                        if(l1->NW==NULL && l1->NE==NULL && l1->SW!=NULL && l1->SE==NULL && l1->SW->internal ==true){
                            return;
                        }
                        if(l1->NW==NULL && l1->NE==NULL && l1->SW==NULL && l1->SE!=NULL && l1->SE->internal ==true){
                            return;
                        }
                        else{
                            if(l1->NW!=NULL && l1->NW->internal == false){
                               
                                if(loc ==1){
                                    pre->NW = l1->NW;
                                }
                                if(loc ==2){
                                    pre->NE = l1->NW;
                                }
                                if(loc ==3){
                                    pre->SW = l1->NW;
                                }
                                if(loc ==4){
                                    pre->SE = l1->NW;
                                }
                                }
                            
                            
                            if(l1->NE!=NULL && l1->NE->internal == false){
                                if(loc ==1){
                                    pre->NW = l1->NE;
                                }
                                if(loc ==2){
                                    pre->NE = l1->NE;
                                }
                                if(loc ==3){
                                    pre->SW = l1->NE;
                                }
                                if(loc ==4){
                                    pre->SE = l1->NE;
                                }

                            
                            }
                            if(l1->SW!=NULL && l1->SW->internal == false){
                                if(loc ==1){
                                    pre->NW = l1->SW;
                                }
                                if(loc ==2){
                                    pre->NE = l1->SW;
                                }
                                if(loc ==3){
                                    pre->SW = l1->SW;
                                }
                                if(loc ==4){
                                    pre->SE = l1->SW;
                                }
                            }
                            
                            if(l1->SE!=NULL && l1->SE->internal == false){
                                if(loc ==1){
                                    pre->NW = l1->SE;
                                }
                                if(loc ==2){
                                    pre->NE = l1->SE;
                                }
                                if(loc ==3){
                                    pre->SW = l1->SE;
                                }
                                if(loc ==4){
                                    pre->SE = l1->SE;
                                }

                            
                            }
                        
                    }
                    }
                    }
                    
                    }
        
                }
    if (l == 2){                                    // to check the location
                if (l1->NE->internal == true){
                    remove(l1->NE,x,y,l1);
                }
                    if(l1->NE->internal ==false){
                        if (l1->NE->xcord == x && l1->NE->ycord == y){
                            delete l1->NE;
                            l1->NE = NULL;
                        
                        if ((l1->NW!=NULL && l1->NE==NULL && l1->SW==NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE!=NULL && l1->SW==NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE==NULL && l1->SW!=NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE==NULL && l1->SW==NULL && l1->SE!=NULL) ){
                            
                            if(l1->NW!=NULL && l1->NE==NULL && l1->SW==NULL && l1->SE==NULL && l1->NW->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE!=NULL && l1->SW==NULL && l1->SE==NULL && l1->NE->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE==NULL && l1->SW!=NULL && l1->SE==NULL && l1->SW->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE==NULL && l1->SW==NULL && l1->SE!=NULL && l1->SE->internal ==true){
                                return;
                            }
                            else{
                                
                                if(l1->NW!=NULL && l1->NW->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->NW;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->NW;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->NW;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->NW;
                                    }

                                
                                    
                                }
                                else if(l1->NE!=NULL && l1->NE->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->NE;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->NE;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->NE;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->NE;
                                    }

                                }
                                else if(l1->SW!=NULL && l1->SW->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->SW;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->SW;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->SW;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->SW;
                                    }

                                }
                                else if(l1->SE!=NULL && l1->SE->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->SE;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->SE;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->SE;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->SE;
                                    }

                                }
                                
                            }
                        }
                    }
                        
                }
            }

            if (l == 3){                                    // to check the location
                if (l1->SW->internal == true){
                    remove(l1->SW,x,y,l1);}
                    if(l1->SW->internal ==false){
                        if (l1->SW->xcord == x && l1->SW->ycord == y){
                            delete l1->SW;
                            l1->SW = NULL;
                        if ((l1->NW!=NULL && l1->NE==NULL && l1->SW==NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE!=NULL && l1->SW==NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE==NULL && l1->SW!=NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE==NULL && l1->SW==NULL && l1->SE!=NULL) ){
                            if(l1->NW!=NULL && l1->NE==NULL && l1->SW==NULL && l1->SE==NULL && l1->NW->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE!=NULL && l1->SW==NULL && l1->SE==NULL && l1->NE->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE==NULL && l1->SW!=NULL && l1->SE==NULL && l1->SW->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE==NULL && l1->SW==NULL && l1->SE!=NULL && l1->SE->internal ==true){
                                return;
                            }
                            else{
                                if(l1->NW!=NULL && l1->NW->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->NW;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->NW;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->NW;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->NW;
                                    }

                                }
                                if(l1->NE!=NULL && l1->NE->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->NE;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->NE;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->NE;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->NE;
                                    }
                                }
                                if(l1->SW!=NULL && l1->SW->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->SW;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->SW;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->SW;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->SW;
                                    }

                                }
                                if(l1->SE!=NULL && l1->SE->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->SE;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->SE;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->SE;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->SE;
                                    }

                                }
                                
                            }
                        }
                    }
                        
                }
            }
 
            if (l == 4){                                    // to check the location
                if (l1->SE->internal == true){
                    remove(l1->SE,x,y,l1);
                }
                    if(l1->SE->internal ==false){
                        if (l1->SE->xcord == x && l1->SE->ycord == y){
                            delete l1->SE;
                            l1->SE = NULL;
                        if ((l1->NW!=NULL && l1->NE==NULL && l1->SW==NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE!=NULL && l1->SW==NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE==NULL && l1->SW!=NULL && l1->SE==NULL) or (l1->NW==NULL && l1->NE==NULL && l1->SW==NULL && l1->SE!=NULL) ){
                            if(l1->NW!=NULL && l1->NE==NULL && l1->SW==NULL && l1->SE==NULL && l1->NW->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE!=NULL && l1->SW==NULL && l1->SE==NULL && l1->NE->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE==NULL && l1->SW!=NULL && l1->SE==NULL && l1->SW->internal ==true){
                                return;
                            }
                            if(l1->NW==NULL && l1->NE==NULL && l1->SW==NULL && l1->SE!=NULL && l1->SE->internal ==true){
                                return;
                            }
                            else{
                                if(l1->NW!=NULL && l1->NW->internal == false){
                                    
                                    if(loc ==1){
                                        pre->NW = l1->NW;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->NW;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->NW;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->NW;
                                    }

                                }
                                if(l1->NE!=NULL && l1->NE->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->NE;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->NE;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->NE;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->NE;
                                    }

                                }
                                if(l1->SW!=NULL && l1->SW->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->SW;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->SW;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->SW;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->SW;
                                    }

                                }
                                if(l1->SE!=NULL && l1->SE->internal == false){
                                    if(loc ==1){
                                        pre->NW = l1->SE;
                                    }
                                    if(loc ==2){
                                        pre->NE = l1->SE;
                                    }
                                    if(loc ==3){
                                        pre->SW = l1->SE;
                                    }
                                    if(loc ==4){
                                        pre->SE = l1->SE;
                                    }
                                }
                            }
                        }
                        }
                       
                        
                    }
                
            }
  
        }
    }
    
    // debug is used to print it in preorder
    void debug(nodequadbase* node){
        if(node == NULL){
            cout<<"E";  //to print E for null values
            return;
        }
        if(node->internal == true){
            cout<<"I";//to print I for internal nodes
            debug(node->NW);
            debug(node->NE);
            debug(node->SW);
            debug(node->SE);
        }
        else{
            cout<<node->xcord<<","<<node->ycord<<" "<<node->name<<"|";
        }
    }
    
    
    
    };


