#include "WanderSlowlyAction.h"

WanderSlowlyAction::WanderSlowlyAction(){}
WanderSlowlyAction::~WanderSlowlyAction(){}

void WanderSlowlyAction::MakeDecision(float dt, Agent* self, Agent* target)
{
	if (self->state == Agent::SEEK_NORMAL || self->state == Agent::SEEK_TIRED)
	{
		self->behaviours.pop_front();
	}

	if (self->behaviours.empty())
	{
		self->AddBehaviour(new Wander());		
	}
	self->state = Agent::WANDER_TIRED;
	self->maxVelocity = 15;
	self->RecoverEnergy();
}
