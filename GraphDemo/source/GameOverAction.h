#pragma once
#include "Decision.h"
#include "GraphDemo.h"
#include <cstdlib>


class GameOverAction :
	public Decision
{
public:
	GameOverAction();
	~GameOverAction();

	virtual void MakeDecision(float dt, Agent* self, Agent* target);
};

