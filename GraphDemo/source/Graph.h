#pragma once
#include "Node.h"
#include "Edge.h"
#include <list>
#include <algorithm>

class Graph
{
public:
	Graph();

	~Graph();

	Node* AddNode(Vector2 data);

	Node* FindNode(Vector2 value);
	void RemoveNode(Node* pNode);
	void FindDijkstrasPath(Node *startNode, Node* endNode, std::list<Node *> &outPath);
	void FindAStar(Node *startNode, Node* endNode, std::list<Node *> &outPath);

	// Helper function, populates “outNodes” with nodes that are within a circular area (xPos, yPos, radious)
	Node* FindNodesInRange(float xPos, float yPos);
	void ConnectNodes(Node* origin, Node* neigh, int value);


	std::vector<Node*> m_nodeList;
protected:
	// List of Nodes
	// (which container type are you going to use)

};