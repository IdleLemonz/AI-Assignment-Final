#include "Decision.h"

Decision::Decision(){}

Decision::~Decision()
{
	delete trueBranch;
	delete falseBranch;
}
