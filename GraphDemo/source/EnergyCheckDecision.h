#pragma once
#include "Decision.h"
class EnergyCheckDecision :
	public Decision
{
public:
	EnergyCheckDecision();
	~EnergyCheckDecision();

	virtual void MakeDecision(float dt, Agent* self, Agent* target);
};

