#include "Graph.h"
#include <algorithm>
#include <vector>
#include <iostream>

Graph::Graph() {}
Graph::~Graph() {}

Node* Graph::AddNode(Vector2 position)
{
	static int ID;
	Node* newNode = new Node(ID++, position);
	m_nodeList.push_back(newNode);
	return newNode;
}

Node* Graph::FindNode(Vector2 value)
{
	Node* temp; // to be rewritten
	return temp;
	/* find node with value */
}
void Graph::RemoveNode(Node* pNode) {	} // remove the given node
										  // Searches the graph starting from the "start" node untill one of the "potential end node's" are found.
										  // the resulting path is added to the "outPath" list.
void Graph::FindDijkstrasPath(Node *startNode, Node* endNode, std::list<Node *> &outPath)
{
	std::list<Node*>pathList;
	for (Node* node : m_nodeList)
	{
		node->gScore = std::numeric_limits<float>::max();
		node->parent = nullptr;
	}

	std::list<Node*>openList;
	std::list<Node*>closedList;
	Node* currentNode = nullptr;
	startNode->gScore = 0;

	openList.push_back(startNode);

	while (!openList.empty())
	{
		openList.sort([](Node* a, Node* b)
		{
			return a->gScore < b->gScore;
		});

		currentNode = openList.front();

		if (currentNode == endNode)
		{
			break;
		}

		openList.remove(currentNode);
		closedList.push_back(currentNode);

		for (Edge c : currentNode->edgeList)
		{			
			//if (std::find(closedList.begin(), closedList.end(), c.m_next) == closedList.end()) // if c.m_next is not in closedList, put it in the open list
			//{
			//	openList.push_back(c.m_next);
			//}

			// the above is the same as
			bool isInClosedList = false;
			for (Node* node : closedList)
			{
				if (node == c.m_next)
				{
					isInClosedList = true;
					break;
				}
			}

			if (!isInClosedList)
			{
				openList.push_back(c.m_next);
			}

			if (currentNode->gScore + c.cost < c.m_next->gScore)
			{
				c.m_next->gScore = currentNode->gScore + c.cost;
				c.m_next->parent = currentNode;
			}
		}
	}
	currentNode = endNode;
	while (currentNode != nullptr)
	{
		pathList.push_front(currentNode);
		currentNode = currentNode->parent;
	}
	outPath = pathList;
}

void Graph::FindAStar(Node *startNode, Node* endNode, std::list<Node *> &outPath)
{
	std::list<Node*>pathList;
	for (Node* node : m_nodeList)
	{
		node->gScore = std::numeric_limits<float>::max();
		node->parent = nullptr;
	}

	std::list<Node*>openList;
	std::list<Node*>closedList;
	Node* currentNode = nullptr;
	startNode->gScore = 0;

	openList.push_back(startNode);

	while (!openList.empty())
	{
		openList.sort([](Node* a, Node* b)
		{
			return a->fScore < b->fScore;
		});

		currentNode = openList.front();

		if (currentNode == endNode)
		{
			break;
		}

		openList.remove(currentNode);
		closedList.push_back(currentNode);

		for (Edge c : currentNode->edgeList)
		{			
			bool isInClosedList = false;
			for (Node* node : closedList)
			{
				if (node == c.m_next)
				{
					isInClosedList = true;
					break;
				}
			}

			if (!isInClosedList)
			{
				openList.push_back(c.m_next);
			}

			if (currentNode->gScore + c.cost < c.m_next->gScore)
			{
				Node* n = c.m_next;
				n->gScore = currentNode->gScore + c.cost;
				n->hScore = n->position.Distance(endNode->position);
				n->fScore = n->gScore + n->hScore;
				n->parent = currentNode;
			}
		}
	}
	currentNode = endNode;
	while (currentNode != nullptr)
	{
		pathList.push_front(currentNode);
		currentNode = currentNode->parent;
	}
	outPath = pathList;
}

//Helper function, populates “outNodes” with nodes that are within a circular area (xPos, yPos, radious)
Node* Graph::FindNodesInRange(float xPos, float yPos){		for (Node* node : m_nodeList)	{				if (node->position.Distance(Vector2(xPos, yPos)) < 50)		{									return node;					}	}	return nullptr;
}

void Graph::ConnectNodes(Node* origin, Node* neigh, int value)
{
	origin->edgeList.push_back(Edge(neigh, value));
	neigh->edgeList.push_back(Edge(origin, value));
}