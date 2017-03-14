#include "OverlappingDecision.h"

OverlappingDecision::OverlappingDecision(){}
OverlappingDecision::~OverlappingDecision(){}

void OverlappingDecision::MakeDecision(float dt, Agent* self, Agent* target)
{
	
	float distFromAgent = self->position.Distance(target->position);

	if (distFromAgent <= 20)
	{
		trueBranch->MakeDecision(dt, self, target);
	}
	else
	{		
		falseBranch->MakeDecision(dt, self, target);
	}
}