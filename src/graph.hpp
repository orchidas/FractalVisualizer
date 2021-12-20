//
//  graph.hpp
//  JuliaSong
//
//  Created by Orchisama Das on 12/19/21.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "vertex.hpp"

#endif /* graph_hpp */

class Graph{
private:
    
    std::vector <Vertex> vertices;
    int numVertices, numEdges;
    int **adjacencyMat;
    float **weightMat;
    std::vector <int> *vertexNeighbors;
    
public:
    
    Graph();
    ~Graph();
    
    int getNumVertices();
    int getNumEdges();
    
    void addVertex(int id);
    void initializeAdjacencyMatrix();
    void addEdge(int startID, int endID, float weight);
    void getNeighbours(int vertexID);
    std::vector <int> djikstraSearch(int sourceID, int targetID);

};
