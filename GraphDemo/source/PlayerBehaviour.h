#pragma once
#include "Agent.h"
#include "Input.h"
#include "glfw3.h"

class PlayerBehaviour : public IBehaviour
{
public:
	PlayerBehaviour();
	~PlayerBehaviour();
	virtual void Update(Agent* self, float deltatime, Agent* hero);
	
	float screenWidth = 1280;
	float screenHeight = 720;	
};

