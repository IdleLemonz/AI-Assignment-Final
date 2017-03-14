#pragma once
#include "Agent.h"

class Decision
{
public:
	Decision();
	~Decision();

	virtual void MakeDecision(float dt, Agent* self, Agent* target) = 0;

	bool value;
	//Agent* owner;
	Decision* trueBranch = nullptr;
	Decision* falseBranch = nullptr;	
};

