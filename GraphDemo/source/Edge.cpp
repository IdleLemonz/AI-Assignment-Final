#include "Edge.h"

Edge::Edge() { m_next = nullptr; }

Edge::Edge(Node *a_connection)
{
	m_next = a_connection;
}

Edge::Edge(Node *a_connection, float a_cost)
{
	m_next = a_connection;
	cost = a_cost;
}

Edge::~Edge() 
{
	//delete m_next;
}

Node* Edge::getNextNode() { return m_next; }