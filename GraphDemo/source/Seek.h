#pragma once
#include "IBehaviour.h"
#include "Agent.h"
#include "GraphDemo.h"
#include "SpriteBatch.h"
#include "Graph.h"
#include <list>

class Node;
class Agent;
class Seek : public IBehaviour
{
public:
	Seek();	
	~Seek();

	SpriteBatch* batch;
	Texture* testerTarget;

	//virtual void Update(Agent* pAgent, float deltatime);	
	virtual void Update(Agent* self, float deltatime, Agent* hero);
	void CreatePath(Agent* pAgent);

	bool hasPath = false;
};

