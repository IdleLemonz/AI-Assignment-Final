
/*-----------------------------------------------------------------------------
Author:			
Description:	
-----------------------------------------------------------------------------*/
#ifndef GraphDemo_H
#define GraphDemo_H

#include "Application.h"
#include <list>
#include <algorithm>

class SpriteBatch;
class Graph;
class Node;
class Texture;
class Agent;

class GraphDemo : public Application
{
public:

	// assets loaded in constructor
	GraphDemo(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title);	

	// assets destroyed in destructor
	virtual ~GraphDemo();

	// update / draw called each frame automaticly
	virtual void Update(float deltaTime);
	virtual void Draw();
	void SetStartNode(Node* node);
	//static void ShortenPath(std::list<Node*> path, Node* start);

	static Node* startNode;
	static Node* endNode;
	static std::list<Node*> AIPath;
	static Graph* m_graph;
	bool keyDown = false;
	bool nodeCheck = true;		

protected:
	SpriteBatch* m_spritebatch;
	Texture* crate;
	Texture* mushroom;
	Texture* poisonMushroom;
	Texture* fireFlower;	
	Texture *m_nodeTexture;
	Font* m_font;
	

	Agent* player;	
	Agent* enemy1;
	
private:
};

#endif