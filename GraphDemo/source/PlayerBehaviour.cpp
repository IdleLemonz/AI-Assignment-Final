#include "PlayerBehaviour.h"

PlayerBehaviour::PlayerBehaviour(){}

PlayerBehaviour::~PlayerBehaviour(){}

void PlayerBehaviour::Update(Agent* self, float deltatime, Agent* hero)
{
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_RIGHT))
	{
		self->AddForce(Vector2(self->increaseSpeed, 0));
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_LEFT))
	{
		self->AddForce(Vector2(-self->increaseSpeed, 0));
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_DOWN))
	{
		self->AddForce(Vector2(0, self->increaseSpeed));
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_UP))
	{
		self->AddForce(Vector2(0, -self->increaseSpeed));
	}
	else
	{
		self->AddForce(Vector2(0, 0) - self->velocity);
	}

	//std::cout << pAgent->position.m_y << "\n";
	//std::cout << pAgent->position.m_x << "\n";

	if (self->position.m_y > screenHeight)
	{
		self->position.m_y = screenHeight;
	}
	else if (self->position.m_y < (screenHeight - screenHeight))
	{
		self->position.m_y = screenHeight - screenHeight;
	}
	else if (self->position.m_x >(screenWidth))
	{
		self->position.m_x = screenWidth;
	}
	else if (self->position.m_x < (screenWidth - screenWidth))
	{
		self->position.m_x = screenWidth - screenWidth;
	}
}


