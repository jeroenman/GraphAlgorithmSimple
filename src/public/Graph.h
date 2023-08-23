#pragma once

#include "Graph.h"
#include "Helper.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NodeRelationship
{
    NodeRelationship(string _nodeFromLabel, string _direction, string _nodeToLabel)
    {
        nodeFromLabel = _nodeFromLabel;
        direction = _direction;
        nodeToLabel = _nodeToLabel;
    }

    string toString()
    {
		return nodeFromLabel + direction + nodeToLabel;
	}

    string nodeFromLabel;
    string nodeToLabel;
    string direction;
};

class Graph
{
    public:
        Graph(string txtFilePath);

        void removeNodesWithEdgeCount(int edgeCount);
        void printNodeRelationships();
        void clean();

    private:
        vector<NodeRelationship*> createNodeRelationships(string txtPath);
        vector<string> getNodesWitIncomingNumberOfEdges(int edgeCount);
        string getStringOfNodeRelationships();

        vector<NodeRelationship*> nodeRelationships;
};