#include "WanderQuicklyAction.h"

WanderQuicklyAction::WanderQuicklyAction(){}

WanderQuicklyAction::~WanderQuicklyAction(){}

void WanderQuicklyAction::MakeDecision(float dt, Agent* self, Agent* target)
{	
	if (self->state == Agent::SEEK_NORMAL || self->state == Agent::SEEK_TIRED)
	{
		self->behaviours.pop_front();
	}

	if (self->behaviours.empty())
	{
		self->AddBehaviour(new Wander());	
	}	
	self->state = Agent::WANDER_NORMAL;
	self->maxVelocity = 50;
	self->RecoverEnergy();
}
