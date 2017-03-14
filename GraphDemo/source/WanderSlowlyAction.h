#pragma once
#include "Decision.h"
#include "Wander.h"

class WanderSlowlyAction : public Decision
{
public:
	WanderSlowlyAction();
	~WanderSlowlyAction();

	virtual void MakeDecision(float dt, Agent* self, Agent* target);
};

