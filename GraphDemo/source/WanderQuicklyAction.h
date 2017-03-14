#pragma once
#include "Decision.h"
#include "IBehaviour.h"
#include "Vector2.h"
#include <random>
#include <iostream>
#include "Agent.h"
#include "IBehaviour.h"
#include "Seek.h"
#include "Wander.h"

class WanderQuicklyAction : public Decision
{
public:
	WanderQuicklyAction();
	~WanderQuicklyAction();

	void MakeDecision(float dt, Agent* self, Agent* target); // implement Wander behaviour


};

