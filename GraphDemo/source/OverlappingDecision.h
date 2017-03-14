#pragma once
#include "Decision.h"
#include "GraphDemo.h"
class OverlappingDecision : public Decision
{
public:
	OverlappingDecision();
	~OverlappingDecision();

	virtual void MakeDecision(float dt, Agent* self, Agent* target);
};

