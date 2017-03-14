#include "Wander.h"

Wander::Wander()
{
	GraphDemo::AIPath.clear();
	GraphDemo::startNode = nullptr;
	GraphDemo::endNode = nullptr;

	// Set random direction
	std::random_device rd; // Create a random number seed
	std::mt19937 mt(rd()); 	// Create random number generator, seed it with 'rd'	
	std::uniform_real_distribution<double> dist(-1.0, 1.0); // set the distribution of random numbers

	wanderDirection.m_x = dist(mt);
	wanderDirection.m_y = dist(mt);
}

Wander::~Wander() {}

void Wander::Update(Agent* self, float deltatime, Agent* hero)
{		
	// Set random jitter
	std::random_device rd; // Create a random number seed
	std::mt19937 mt(rd()); 	// Create random number generator, seed it with 'rd'	
	std::uniform_real_distribution<double> dist(-0.1, 0.1); // set the distribution of random numbers	
	jitter.m_x = dist(mt);
	jitter.m_y = dist(mt);

	// keeping agent within the screen
	if (self->position.m_y > screenHeight)
	{
		self->position.m_y = screenHeight;		
		wanderDirection.m_y = wanderDirection.m_y * -1;
		self->velocity.m_y = self->velocity.m_y * -1;
	}
	else if (self->position.m_y < (screenHeight - screenHeight))
	{
		self->position.m_y = screenHeight - screenHeight;
		wanderDirection.m_y = wanderDirection.m_y * -1;
		self->velocity.m_y = self->velocity.m_y * -1;
	}
	else if (self->position.m_x > (screenWidth))
	{
		self->position.m_x = screenWidth;
		wanderDirection.m_x = wanderDirection.m_x * -1;
		self->velocity.m_x = self->velocity.m_x * -1;
	}
	else if (self->position.m_x < (screenWidth - screenWidth))
	{
		self->position.m_x = screenWidth - screenWidth;
		wanderDirection.m_x = wanderDirection.m_x * -1;
		self->velocity.m_x = self->velocity.m_x * -1;
	}

	self->RecoverEnergy();

	// wandering code
	target = self->position + self->velocity + wanderDirection * radius;

	Vector2 force;
	force = Vector2::Normalise(target - self->position) * self->maxVelocity;
	self->AddForce(force - self->velocity);	

	wanderDirection = wanderDirection + jitter;	
	wanderDirection.Normalise();
}



