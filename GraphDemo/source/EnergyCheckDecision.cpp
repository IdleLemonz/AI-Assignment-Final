#include "EnergyCheckDecision.h"

EnergyCheckDecision::EnergyCheckDecision(){}
EnergyCheckDecision::~EnergyCheckDecision(){}

void EnergyCheckDecision::MakeDecision(float dt, Agent* self, Agent* target)
{	
	if (self->state == Agent::SEEK_NORMAL || self->state == Agent::WANDER_NORMAL)
	{		
		std::cout << "Has energy\n";
		trueBranch->MakeDecision(dt, self, target); // if has energy, move normally
	}
	if (self->state == Agent::SEEK_TIRED || self->state == Agent::WANDER_TIRED)
	{				
		std::cout << "No energy\n";
		falseBranch->MakeDecision(dt, self, target); // if no energy, move slowly
	}
}
