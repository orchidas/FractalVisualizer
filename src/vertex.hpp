//
//  vertex.hpp
//  JuliaSong
//
//  Created by Orchisama Das on 12/19/21.
//

#ifndef vertex_hpp
#define vertex_hpp

#include <stdio.h>



class Vertex{

private:
    int numID;
    
public:
    Vertex(){numID = -1;}
    
    Vertex(int ID){numID = ID;}
    
    ~Vertex(){};
    
    int getID(){return numID;}
};

#endif /* vertex_hpp */
