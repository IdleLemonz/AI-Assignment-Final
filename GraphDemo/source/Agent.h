#pragma once
#include "Vector2.h"
#include "IBehaviour.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Node.h"
#include <iostream>
#include <list>

class Texture;
class PlayerBehaviour;
class Seek;
class Wander;
class Decision;
class CheckDistanceDecision;
class SeekQuicklyAction;
class SeekSlowlyAction;
class WanderQuicklyAction;
class WanderSlowlyAction;
class OverlappingDecision;
class EnergyCheckDecision;
class GameOverAction;

class Agent
{
public:
	Agent();
	Agent(int xPos, int yPos);
	Agent(int xPos, int yPos, float veloc);
	Agent(int xPos, int yPos, float veloc, Vector2 newTarget);
	~Agent();

	enum AgentType 
	{
		HERO,
		ENEMY
	};	
	AgentType type;

	enum AgentState
	{
		WANDER_NORMAL,
		WANDER_TIRED,
		SEEK_NORMAL,
		SEEK_TIRED
	};
	AgentState state;

	virtual void Update(float deltaTime);	
	void AddForce(Vector2 newForce);
	void AddBehaviour(IBehaviour* state);
	void SetAgentType(AgentType newType);
	void SetTarget(Vector2 newTarget);
	void SetTarget(Node* startNode, Agent* hero);
	void Draw(SpriteBatch* pass);
	void Draw(SpriteBatch* pass, int width, int height);
	Vector2 GetDirection();
	void RecoverEnergy();
	void LoseEnergy();
	void CheckEnergy();
	void CreateTree();

	Vector2 position;
	Vector2 force;
	Vector2 maxForce;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 direction;
	Vector2 targetPos;
	unsigned int maxEnergy = 200;
	unsigned int energy = 200;
	float maxVelocity;	
	float angle;		
	float increaseSpeed = 300;	
	Texture* m_sprite;
	Agent* m_hero = nullptr;

	Decision* treeRoot = nullptr;

	std::list<IBehaviour*> behaviours;
};

