#pragma once
#include "IBehaviour.h"
#include "Vector2.h"
#include <random>
#include <iostream>
#include "Agent.h"
#include "IBehaviour.h"
#include "Seek.h"

class Wander :
	public IBehaviour
{
public:
	Wander();	
	~Wander();

	virtual void Update(Agent* self, float deltatime, Agent* hero);
		
	const double pi = 3.141592653589793;

	Vector2 target;
	Vector2 wanderDirection; // To initialise wander direction, generate a random number for the x and y positions, then normalise it
	Vector2 jitter;
	float radius = 8;	
	float screenWidth = 1280;
	float screenHeight = 720;

		//float radius = 
};

