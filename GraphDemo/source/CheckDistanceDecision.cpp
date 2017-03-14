#include "CheckDistanceDecision.h"

CheckDistanceDecision::CheckDistanceDecision(){	}

CheckDistanceDecision::~CheckDistanceDecision()
{	
}

void CheckDistanceDecision::MakeDecision(float dt, Agent* self, Agent* target)
{
	float distFromAgent = self->position.Distance(target->position); // compares the distance of the agent from the startNode of AI path

	if (distFromAgent <= 500)
	{
		trueBranch->MakeDecision(dt, self, target); // if close, seek the target
		//lastDecision = trueBranch;
	}		
	else
	{
		falseBranch->MakeDecision(dt, self, target); // else, wander
		//lastDecision = falseBranch;
	}
		
}