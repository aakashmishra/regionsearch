//
//  leafnode.h
//  regionsearch
//
//  Created by Aakash Anand Mishra on 11/9/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//

#ifndef regionsearch_leafnode_h
#define regionsearch_leafnode_h

#endif
#include "quadnode.h"
#include "internalnode.h"
#include <string>
#include <iostream>


class leafnode : public nodequadbase{
public:
    leafnode(){
        xcord = 0;
        ycord = 0;
        name = "";
        child = 0;
        internal= false;
        NW =NULL;
        NE =NULL;
        SW =NULL;
        SE =NULL;
      
    }
    leafnode(int x, int y, string cityname){
        
        xcord = x;
        ycord = y;
        name = cityname;
        child = 0;
        internal= false;
        NW =NULL;
        NE =NULL;
        SW =NULL;
        SE =NULL;
     
        
        
    }
};

