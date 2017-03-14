#pragma once
#include "IBehaviour.h"
#include "Agent.h"
#include "Node.h"
#include <list>

class Node;
class Agent;
class Flee : public IBehaviour
{
public:
	Flee();
	~Flee();

	virtual void Update(Agent* pAgent, float deltatime);
};

