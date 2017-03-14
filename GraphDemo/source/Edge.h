#pragma once
#include "Node.h"

class Node;
class Edge
{
public:
	Edge();
	Edge(Node *a_connection);
	Edge(Node *a_connection, float a_cost);
	~Edge();

	Node* getNextNode();

	Node *m_next = nullptr;
	int cost = 0;
};