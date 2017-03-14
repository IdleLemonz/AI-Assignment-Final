#include "Flee.h"


Flee::Flee(){}

Flee::~Flee(){}

void Flee::Update(Agent* pAgent, float deltatime)
{
	if (pAgent->targetPos != nullptr)
	{
		Vector2 force;
		force = Vector2::Normalise(pAgent->position - pAgent->targetPos) * pAgent->maxVelocity;

		pAgent->AddForce(force - pAgent->velocity);
	}
}
