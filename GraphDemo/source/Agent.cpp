#include "Agent.h"
#include "Texture.h"
#include <iostream>
#include "Wander.h"
#include "Seek.h"
#include "PlayerBehaviour.h"
#include "Decision.h"
#include "CheckDistanceDecision.h"
#include "SeekQuicklyAction.h"
#include "SeekSlowlyAction.h"
#include "WanderQuicklyAction.h"
#include "WanderSlowlyAction.h"
#include "OverlappingDecision.h"
#include "EnergyCheckDecision.h"
#include "GameOverAction.h"

Agent::Agent()
{	
	maxForce.m_x = 50;
	maxForce.m_y = 50;
	maxVelocity = 90;
	position.m_x = 200;
	position.m_y = 300;
	velocity.m_x = 0;
	velocity.m_y = 0;
	angle = 0;	
}

Agent::Agent(int xPos, int yPos)
{	
	maxForce.m_x = 50;
	maxForce.m_y = 50;
	maxVelocity = 90;
	position.m_x = xPos;
	position.m_y = yPos;
	velocity.m_x = 0;
	velocity.m_y = 0;
	angle = 0;	
}

Agent::Agent(int xPos, int yPos, float veloc)
{	
	maxForce.m_x = 50;
	maxForce.m_y = 50;
	maxVelocity = veloc;
	position.m_x = xPos;
	position.m_y = yPos;
	velocity.m_x = 0;
	velocity.m_y = 0;
	angle = 0;	
}

Agent::Agent(int xPos, int yPos, float veloc, Vector2 newTarget)
{	
	maxForce.m_x = 50;
	maxForce.m_y = 50;
	maxVelocity = veloc;
	position.m_x = xPos;
	position.m_y = yPos;
	velocity.m_x = 0;
	velocity.m_y = 0;
	angle = 0;
	targetPos = newTarget;
}

Agent::~Agent()
{
	delete m_sprite;
}

void Agent::Update(float deltaTime)
{
	static int inter = 0;

	velocity = velocity + (force * deltaTime);

	if (velocity.Length() > maxVelocity)
	{
		Vector2 temp = velocity.Normalise();
		velocity = temp * maxVelocity;
	}

	position = position + (velocity * deltaTime);
	force = Vector2(0, 0);

	GetDirection();	
	CheckEnergy();

	if (treeRoot != nullptr)
	{
		treeRoot->MakeDecision(deltaTime, this, m_hero);
	}
		
	for (IBehaviour* be : behaviours)
	{		
		be->Update(this, deltaTime, m_hero);
	}	
	
}

void Agent::AddForce(Vector2 newForce)
{	
	force = force + newForce;	
}

void Agent::AddBehaviour(IBehaviour* state)
{
	behaviours.push_back(state);
}

void Agent::SetAgentType(AgentType newType)
{
	type = newType;
	if (newType == HERO)
	{
		m_sprite = new Texture("./Images/mario.png");
		AddBehaviour(new PlayerBehaviour());
	}
	else if (newType == ENEMY)
	{		
		m_sprite = new Texture("./Images/goomba.png");	
		state = WANDER_NORMAL;
		CreateTree();
	}	
}

void Agent::SetTarget(Vector2 newTarget)
{
	targetPos = newTarget;
}

void Agent::SetTarget(Node* startNode, Agent* hero)
{
	if (state == WANDER_NORMAL || state == WANDER_TIRED)
	{
		targetPos = this->position;
	}
	else if (state == SEEK_NORMAL || state == SEEK_TIRED)
	{
		if (startNode != nullptr)
		{
			targetPos = startNode->position;
		}		
	}
	m_hero = hero;
}

void Agent::Draw(SpriteBatch* pass)
{
	pass->DrawSprite(m_sprite, position.m_x, position.m_y, 60, 60, angle);
}

void Agent::Draw(SpriteBatch* pass, int width, int height)
{
	pass->DrawSprite(m_sprite, position.m_x, position.m_y, width, height, angle);
}

Vector2 Agent::GetDirection()
{
	direction = this->velocity.Normalise();
	angle = atan2f(direction.m_y, direction.m_x);
	return direction;
}

void Agent::RecoverEnergy()
{
	if (energy < maxEnergy)
	{
		energy++;
	}
}

void Agent::LoseEnergy()
{
	if (energy > 0)
	{
		energy--;
	}
}

void Agent::CheckEnergy()
{
	if (type == ENEMY)
	{
		//std::cout << "Energy levels: " << energy << "\n";
		// Change movement state depending on current state and energy levels
		if (state == WANDER_NORMAL && energy < (maxEnergy / 3))
		{			
			state = WANDER_TIRED;
		}

		if (state == WANDER_TIRED && energy >= (maxEnergy / 3))
		{
			
			state = WANDER_NORMAL;
		}

		if (state == SEEK_NORMAL && energy == 0)
		{			
			state = SEEK_TIRED;
		}

		if (state == SEEK_TIRED && energy >= (maxEnergy / 2))
		{			
			state = SEEK_NORMAL;
		}
	}	
}

void Agent::CreateTree()
{
	// make the tree	
	treeRoot = new CheckDistanceDecision(); // check distance from player
	treeRoot->trueBranch = new OverlappingDecision(); // check if player is overlapping enemy
	treeRoot->falseBranch = new EnergyCheckDecision(); // check if enemy has energy

	Decision* temp = treeRoot->falseBranch;
	temp->trueBranch = new WanderQuicklyAction(); // if has energy, wander quickly
	temp->falseBranch = new WanderSlowlyAction(); // if no energy, wander slowly

	Decision* temp2 = treeRoot->trueBranch;	
	temp2->trueBranch = new GameOverAction(); // if overlapping hero, game over
	temp2->falseBranch = new EnergyCheckDecision(); // if not overlapping hero, check energy

	temp = nullptr;
	temp = temp2->falseBranch;	
	temp->trueBranch = new SeekQuicklyAction(); // if has energy, seek quickly
	temp->falseBranch = new SeekSlowlyAction(); // if no energy, seek slowly
}