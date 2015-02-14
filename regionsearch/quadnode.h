//
//  quadnode.h
//  regionsearch
//
//  Created by Aakash Anand Mishra on 11/9/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//

#ifndef regionsearch_quadnode_h
#define regionsearch_quadnode_h



class  nodequadbase{
public:
    int xcord;
    int ycord;
    int range;
    string name;
    
    int child;
    bool internal;
    nodequadbase* NW;
    nodequadbase* NE;
    nodequadbase* SE;
    nodequadbase* SW;
   
    
    
    virtual ~nodequadbase()
    {
        
    }
    
};
#endif