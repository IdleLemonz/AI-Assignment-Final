#pragma once
#include "Decision.h"

class CheckDistanceDecision : public Decision
{
public:
	CheckDistanceDecision();	
	~CheckDistanceDecision();

	void MakeDecision(float dt, Agent* self, Agent* target);

	
};

