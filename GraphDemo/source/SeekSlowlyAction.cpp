#include "SeekSlowlyAction.h"

SeekSlowlyAction::SeekSlowlyAction(){}
SeekSlowlyAction::~SeekSlowlyAction(){}

void SeekSlowlyAction::MakeDecision(float dt, Agent* self, Agent* target)
{	
	if (self->state == Agent::WANDER_NORMAL || self->state == Agent::WANDER_TIRED)
	{
		self->behaviours.pop_front();
	}

	if (self->behaviours.empty()) // if the behaviour list isn't empty, add a new behaviour
	{		
		self->AddBehaviour(new Seek());				
	}
	//std::cout << "Seeking Slowly\n";
	self->state = Agent::SEEK_TIRED;
	self->maxVelocity = 45;
	self->RecoverEnergy();
}
