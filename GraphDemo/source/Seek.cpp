#include "Seek.h"
#include "Node.h"
#include <algorithm>

Seek::Seek(){}
Seek::~Seek(){}

void Seek::Update(Agent* self, float deltatime, Agent* hero)
{
	m_hero = hero;
	if (self->targetPos != nullptr)
	{
		Vector2 force;
		force = Vector2::Normalise(self->targetPos - self->position) * (self->maxVelocity);
		self->AddForce(force - self->velocity);			
	}		

	CreatePath(self);

	if ((GraphDemo::startNode != nullptr && !GraphDemo::AIPath.empty()) && hasPath) 
	{
		bool executed = false;
		float distFromAgent = self->position.Distance(GraphDemo::startNode->position); // compares the distance of the agent from the startNode of AI path
		if (distFromAgent <= 30 && distFromAgent>3) // if the agent is close enough, shift the startNode to the next node in the path, then remove the first node from the path		
		{			
			for (Node* node : GraphDemo::AIPath)
			{					
				if (executed == false)
				{
					float dist2ndNode = GraphDemo::startNode->position.Distance(node->position); // Finds the second node in the path																				
					if (dist2ndNode <= 100 && dist2ndNode > 3) // compares the distance of the startNode to the next node, looking for the first closest one
					{						
						GraphDemo::startNode = node; // set the start node to the next node in the path / list						
						GraphDemo::AIPath.pop_front(); // remove the first node in the path / list		
						executed = true;
					}
				}
				else if (executed == true)
				{
					break;
				}				
			}			
		}		
	}	
}

void Seek::CreatePath(Agent* self)
{		
	if (GraphDemo::startNode != nullptr && GraphDemo::endNode != nullptr) // check if the startNode and endNode are not nullptr
	{		
		if (GraphDemo::startNode->position == GraphDemo::endNode->position) // check if their positions are the same
		{
			GraphDemo::AIPath.clear();
			GraphDemo::startNode = nullptr;
			GraphDemo::endNode = nullptr;
		}
	}	
	
	if (GraphDemo::startNode == nullptr) // if startNode != nullptr// set the startNodes
	{			
		GraphDemo::startNode = GraphDemo::m_graph->FindNodesInRange(self->position.m_x, self->position.m_y);
	}

	if (GraphDemo::endNode == nullptr && m_hero != nullptr) // if endNode != nullptr, set the endNodes
	{		
		GraphDemo::endNode = GraphDemo::m_graph->FindNodesInRange(m_hero->position.m_x, m_hero->position.m_y);
	}

	if (GraphDemo::startNode != nullptr && GraphDemo::endNode != nullptr) // startNode != nullptr && endNode != nullptr
	{
		GraphDemo::m_graph->FindAStar(GraphDemo::startNode, GraphDemo::endNode, GraphDemo::AIPath);
		hasPath = true;
	}
	else
	{
		hasPath = false;
	}
}

