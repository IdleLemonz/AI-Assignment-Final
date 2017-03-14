#pragma once
#include "Decision.h"
#include "Seek.h"

class SeekQuicklyAction : public Decision
{
public:
	SeekQuicklyAction();
	~SeekQuicklyAction();

	void MakeDecision(float dt, Agent* self, Agent* target); // implement Seek behaviour
};

