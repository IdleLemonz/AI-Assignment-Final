#pragma once
#include "Node.h"
#include <list>

class Node;
class Agent;
class IBehaviour
{
public:
	IBehaviour();
	~IBehaviour();

	virtual void Update(Agent* pAgent, float deltatime, Agent* hero) = 0;

	Agent* m_hero;
};

