#pragma once

#include "Vector2.h"
#include "Edge.h"
#include <vector>

class Edge;
class Node
{
public:
	Node();
	Node(Vector2 a_pos);
	Node(int id, Vector2 value);
	Node(Vector2 a_pos, float a_gScore, Node *a_parent);
	~Node();

	bool visited = false;
	int m_ID;
	float gScore = 0;
	float hScore = 0;
	float fScore = 0;
	Vector2 position;
	Node* parent;
	Node* originNode;

	std::vector<Edge> edgeList;
};