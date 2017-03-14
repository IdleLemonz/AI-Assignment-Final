#pragma once
#include "Decision.h"
#include "Seek.h"

class SeekSlowlyAction : public Decision
{
public:
	SeekSlowlyAction();
	~SeekSlowlyAction();

	virtual void MakeDecision(float dt, Agent* self, Agent* target);
};

