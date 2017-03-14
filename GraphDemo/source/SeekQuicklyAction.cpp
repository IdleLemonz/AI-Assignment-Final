#include "SeekQuicklyAction.h"

SeekQuicklyAction::SeekQuicklyAction(){}

SeekQuicklyAction::~SeekQuicklyAction(){}

void SeekQuicklyAction::MakeDecision(float dt, Agent* self, Agent* target)
{
	if (self->state == Agent::WANDER_NORMAL || self->state == Agent::WANDER_TIRED)
	{
		self->behaviours.pop_front();
	}
	
	if (self->behaviours.empty()) // if the behaviour list isn't empty, add a new behaviour
	{		
		self->AddBehaviour(new Seek());			
	}	
	//std::cout << "Seeking Quickly\n";
	self->state = Agent::SEEK_NORMAL;
	self->maxVelocity = 500;
	self->LoseEnergy();
}
