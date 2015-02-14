//
//  internalnode.h
//  regionsearch
//
//  Created by Aakash Anand Mishra on 11/9/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//

#ifndef regionsearch_internalnode_h
#define regionsearch_internalnode_h

#include "quadnode.h"
class internalnode : public nodequadbase{
public:
    internalnode(){
        xcord = 0;
        ycord = 0;
        range = 0;
        internal = true;
        child = 0;
        NW = NULL;
        NE = NULL;
        SE = NULL;
        SW = NULL;
 
        
    }
    internalnode(int x, int y, int rang)
    {xcord = x;
        ycord = y;
        range = rang;
        internal = true;
        child = 0;
        NW = NULL;
        NE = NULL;
        SE = NULL;
        SW = NULL;
  
    }
};

#endif