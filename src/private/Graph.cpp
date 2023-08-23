#include "Graph.h"
#include "Helper.h"
#include <unordered_map>

Graph::Graph(string txtFilePath)
{
    nodeRelationships = createNodeRelationships(txtFilePath);
}

vector<NodeRelationship*> Graph::createNodeRelationships(string txtPath)
{
    vector<NodeRelationship*> nodesRelationships;
    nodesRelationships.reserve(10);

    string s;
    ifstream in;

    in.open(txtPath);

    if (!in.is_open())
    {
        std::cerr << "Could not open file located at: "+ txtPath << std::endl;
        return nodesRelationships;
    }

    // CREATE A NodeRelationship FOR EACH LINE / RELATIONSHIP
    while (!in.eof())
    {
        getline(in, s);

        NodeRelationship* nodesRelationship = new NodeRelationship(s.substr(0, 1), s.substr(1, 2), s.substr(3, 1));
        nodesRelationships.push_back(nodesRelationship);
    }

    return nodesRelationships;
}

vector<string> Graph::getNodesWitIncomingNumberOfEdges(int edgeCount)
{
    // GET ALL UNIQUE LETTERS IN MAP
    unordered_map<string, int> uniqueNodes;
    for (NodeRelationship* nodeRelationship : nodeRelationships)
    {
        uniqueNodes[nodeRelationship->nodeFromLabel] = 0;
        uniqueNodes[nodeRelationship->nodeToLabel] = 0;
    }

    // STORE ALL INCOMING EDGES FOR EACH LETTER
    for (NodeRelationship* nodeRelationship : nodeRelationships)
    {
        if (nodeRelationship->direction == "->")
        {
            uniqueNodes[nodeRelationship->nodeToLabel]++;
        }
        else
        if (nodeRelationship->direction == "<-")
        {
            uniqueNodes[nodeRelationship->nodeFromLabel]++;
        }
        else
        if (nodeRelationship->direction == "<>")
        {
            uniqueNodes[nodeRelationship->nodeToLabel]++;
            uniqueNodes[nodeRelationship->nodeFromLabel]++;
        }
    }

    // REUSE uniqueNodes TO STORE ONLY THE NODES WITH THE SPECIFIED NUMBER OF INCOMING EDGES
    for (auto it = uniqueNodes.begin(); it != uniqueNodes.end(); )
    {
        if (it->second != edgeCount)
        {
            it = uniqueNodes.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // MAKE VECTOR OF LETTERS OUT OF MAP
    vector<string> keys;
    for (const auto& pair : uniqueNodes)
    {
        keys.push_back(pair.first);
    }

    return keys;
}

void Graph::removeNodesWithEdgeCount(int edgeCount)
{
    vector<string> nodeLetters = getNodesWitIncomingNumberOfEdges(edgeCount);

    int nodeRelationshipsLength = static_cast<int>(nodeRelationships.size());
    for (int i = nodeRelationshipsLength - 1; i >= 0; i--)
    {
        NodeRelationship* nodeRelationship = nodeRelationships[i];

        // IF nodeRelationship CONTAINS ANY OF THE LETTER TO REMOVE, REMOVE IT
        if (getIndexOfElementInVector(nodeLetters, nodeRelationship->nodeFromLabel) != -1 || getIndexOfElementInVector(nodeLetters, nodeRelationship->nodeToLabel) != -1)
        {
            spliceVectorAtIndex(nodeRelationships, i);
            delete nodeRelationship;
		}
    }
}

string Graph::getStringOfNodeRelationships()
{
    string result = "";

    int nodeRelationshipsLength = static_cast<int>(nodeRelationships.size());
    for (int i = 0; i < nodeRelationshipsLength; i++)
    {
		NodeRelationship* nodeRelationship = nodeRelationships[i];
		result += nodeRelationship->toString() + "\n";
	}

    return result;
}

void Graph::printNodeRelationships()
{
    string nodeRelationshipStr = getStringOfNodeRelationships();
    cout << nodeRelationshipStr;
}

void Graph::clean()
{
    // CLEANUP nodeRelationships
    for (NodeRelationship* nodeRelationship : nodeRelationships)
    {
        delete nodeRelationship;
    }
}