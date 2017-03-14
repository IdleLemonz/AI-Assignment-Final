#include "Node.h"

Node::Node() { m_ID = 0; parent = nullptr; }
Node::Node(Vector2 a_pos)
{
	position = a_pos;
	parent = nullptr;
}
Node::Node(Vector2 a_pos, float a_gScore, Node *a_parent)
{
	position = a_pos;
	gScore = a_gScore;
	parent = a_parent;
}
Node::~Node() {}
Node::Node(int id, Vector2 value) { m_ID = id; position = value; }
