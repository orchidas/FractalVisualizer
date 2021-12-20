//
//  graph.cpp
//  JuliaSong
//
//  Created by Orchisama Das on 12/19/21.
//

#include "graph.hpp"

Graph::Graph(){
    
    numEdges = 0;
    numVertices = 0;
    
}

Graph::~Graph(){}

void Graph::addVertex(int id){
    Vertex V(id);
    vertices.push_back(V);
    numVertices++;
 
}


void Graph::initializeAdjacencyMatrix(){
    
    adjacencyMat = new int* [numVertices];
    weightMat = new float* [numVertices];
    vertexNeighbors = new std::vector<int> [numVertices];
    for(int i = 0; i < numVertices; i++){
        adjacencyMat[i] = new int[numVertices];
        weightMat[i] = new float[numVertices];
        for (int j = 0; j < numVertices; j++){
            adjacencyMat[i][j] = 0;
            weightMat[i][j] = 0.0;
        }
    }
}
    
    

void Graph::addEdge(int startID, int endID, float weight){
    
    adjacencyMat[startID][endID] = 1;
    weightMat[startID][endID] = weight;
    vertexNeighbors[startID].push_back(endID);
    numEdges++;
}


int Graph::getNumEdges(){ return numEdges;}
int Graph::getNumVertices(){ return numVertices;}



//Djikstra's search to find shortest path in weighted graph
std::vector <int> Graph::djikstraSearch(int sourceID, int targetID){
    

    Vertex notDefined;
    
    //crete vertex set Q
    std::vector <Vertex> Q;
    std::vector <int> S; // to store path indices
    std::map <int, Vertex> prevVisited;
    std::map <int, float> dist;
    int minElem, n;
    float minElemDist;
    int niter = 0;
    
    //initialize
    for (auto elem : vertices){
        dist[elem.getID()] = 9999.9;
        prevVisited[elem.getID()] = notDefined;
        Q.push_back(elem);
    }
        
    dist[sourceID] = 0.0;
        
    while (!Q.empty()){
        
        //search for vertex in the vertex set that has minimum dist value
        n = 0; minElem = -1;
        minElemDist = 9999.9;
        for(auto it = Q.begin(); it != Q.end(); ++it){
            if (dist[(*it).getID()] <= minElemDist){
                minElemDist = dist[(*it).getID()];
                minElem = n;
            }
            n++;
        }
        Vertex u = Q.at(minElem);
        
        
        if(Q.empty()){
            std::cout << "No path could be found! No of iterations = " << niter << std::endl;
            return S;
        }
        
        //path has been found
        if (u.getID() == targetID){
            //if (prevVisited[u.getID()].getID() != -1 || u.getID() == sourceID){
                while (u.getID() != -1){
                    S.push_back(u.getID());
                    u = prevVisited[u.getID()];
                }
                //reverse S because path is traversed in reverse order
                std::reverse(S.begin(), S.end());
                return S;
            //}
            
        }
        else{
        
            //for each neihgbour of u still in Q
            for(auto u : Q){
                for (auto v : vertexNeighbors[u.getID()]){
                    float alt = dist[u.getID()] + weightMat[u.getID()][v];
                    if (alt < dist[v]){
                        dist[v] = alt;
                        prevVisited[v] = u;
                    }
                }
            }
            //remove u from Q
            Q.erase(Q.begin() + minElem);
            niter++;
        }
    }

    return S;

}
