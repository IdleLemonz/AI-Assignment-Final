#include "GraphDemo.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Graph.h"
#include "Agent.h"
#include "PlayerBehaviour.h"
#include "Seek.h"
#include "Wander.h"
#include "Flee.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>

Node* GraphDemo::startNode = nullptr;
Node* GraphDemo::endNode = nullptr;
std::list<Node*> GraphDemo::AIPath;
Graph* GraphDemo::m_graph = nullptr;

GraphDemo::GraphDemo(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);	
	m_graph = new Graph();

	startNode = nullptr;
	endNode = nullptr;

	//float graphScale = 2.5f;
	Node* temp;
	int graphWidth = 100; // the space between the node widths
	int graphHeight = 100; // the space between the node heights
	int widthOffset = 100; // the offset of the rows from the left side of the screen
	int heightOffset = 100; // the offset of the columns from the top of the screen
	for (int i = 1; i <= 14; i++)
	{		
		for (int j = 1; j <= 8; j++)
		{			
			m_graph->AddNode(Vector2(((graphWidth * i) - widthOffset), ((graphHeight * j) - heightOffset )));
		}
	}
	heightOffset = 50;
	widthOffset = 50;
	for (int i = 1; i <= 13; i++)
	{
		for (int j = 1; j <= 7; j++)
		{
			m_graph->AddNode(Vector2((graphWidth * i - widthOffset), (graphHeight * j - heightOffset)));
		}
	}

	for (Node* nodeStart : m_graph->m_nodeList)
	{
		for (Node* nodeNext : m_graph->m_nodeList)
		{
			float dist = nodeStart->position.Distance(nodeNext->position);
			if (dist <= 100 && dist>3)
			{
				m_graph->ConnectNodes(nodeStart, nodeNext, nodeStart->position.Distance(nodeNext->position));
			}
		}		
	}

	/*Node *a = m_graph->AddNode(Vector2(100 * graphScale, 100 * graphScale));
	Node *b = m_graph->AddNode(Vector2(150 * graphScale, 100 * graphScale));
	m_graph->ConnectNodes(a, b, 1);*/

	m_nodeTexture = new Texture("./Images/nodeTexture.png");
	mushroom = new Texture("./Images/mushroom.png");
	poisonMushroom = new Texture("./Images/poisonMushroom.png");
	crate = new Texture("./Images/crate.png");
	fireFlower = new Texture("./Images/fireFlower.png");
	m_font = new Font("./Fonts/arial_20px.fnt");

	player = new Agent(700, 250, 300);
	player->SetAgentType(Agent::HERO);
	//player->AddBehaviour(new PlayerBehaviour());

	enemy1 = new Agent(100, 100);
	enemy1->SetAgentType(Agent::ENEMY);
	enemy1->SetTarget(startNode, player);	
}

GraphDemo::~GraphDemo()
{
	SpriteBatch::Factory::Destroy(m_spritebatch);
	delete m_nodeTexture;
	delete crate;
	delete m_font;
	delete m_graph;
	delete player;
	delete enemy1;
}

void GraphDemo::Update(float deltaTime)
{
	if (Input::GetSingleton()->WasMouseButtonPressed(0)) // check for left click
	{
		int mx, my; 
		Input::GetSingleton()->GetMouseXY(&mx, &my); // get mouse position 

		Node* newNode = m_graph->AddNode(Vector2(mx, my)); // add node to the graph at mouse position

		for (Node* node : m_graph->m_nodeList)  // iterate through the node list and connect the nodes if they fit the distance check
		{
			float dist = node->position.Distance(newNode->position);
			if (dist < 100 && dist>3)
			{
				m_graph->ConnectNodes(node, newNode, node->position.Distance(newNode->position));
			}
		}
	}

	if (Input::GetSingleton()->WasMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) // checks for right click
	{
		int mx, my;
		Input::GetSingleton()->GetMouseXY(&mx, &my); // get mouse position 

		// set the start and end nodes, or reset them if they are both already set
		if (!startNode) // startNode == nullptr
		{
			startNode = m_graph->FindNodesInRange(mx, my);
		}
		else if (!endNode) // endNode == nullptr
		{
			endNode = m_graph->FindNodesInRange(mx, my);
		}
		else if (startNode && endNode) // startNode != nullptr && endNode != nullptr
		{
			startNode = nullptr;
			endNode = nullptr;
		}
	}

	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_E))
	{
		// clear the path and reset the start and end nodes
		AIPath.clear();
		startNode = nullptr;
		endNode = nullptr;
	}

	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_R)) // if key R is pressed, use Dijkstra's algorithm to find a path
	{
		if (startNode && endNode) // startNode != nullptr && endNode != nullptr
		{
			m_graph->FindDijkstrasPath(startNode, endNode, AIPath);
		}
	}

	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_T)) // if key T is pressed, use AStar algorithm to find a path
	{
		if (startNode && endNode) // startNode != nullptr && endNode != nullptr
		{
			m_graph->FindAStar(startNode, endNode, AIPath);
		}
	}

	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_Q) && keyDown == false) // if key Q is pressed, move the startNode to the next node in the path, shortening the path
	{	
		keyDown = true;
		bool executed = false;
		for (Node* node : AIPath)
		{	
			if (executed == false)
			{
				float dist = startNode->position.Distance(node->position);
				if (dist <= 100 && dist>3)
				{
					startNode = node; // set the start node to the next node in the path / list
					AIPath.pop_front(); // remove the first node in the path / list								
					executed = true;								
				}
			}		
			else if (executed == true)
			{
				break;
			}
		}		 
	}

	if (Input::GetSingleton()->IsKeyUp(GLFW_KEY_Q))
	{
		keyDown = false;
	}	

	enemy1->SetTarget(startNode, player);	
	player->Update(deltaTime); // updates with delta time
	enemy1->Update(deltaTime); // updates with delta time and the new position of the target every frame	
}

void GraphDemo::Draw()
{
	// clear the back buffer
	ClearScreen();

	m_spritebatch->Begin();

	for (auto& it : m_graph->m_nodeList) // it = the individual nodes in the node list
	{
		for (auto& it2 : it->edgeList) // it = the individual node in the list    it2 = the individual edges of the edgeList
		{
			m_spritebatch->DrawLine(it->position.m_x, it->position.m_y, it2.m_next->position.m_x, it2.m_next->position.m_y);
		}
	}

	for (auto& it : m_graph->m_nodeList) // it = the individual nodes in the node list
	{
		m_spritebatch->DrawSprite(m_nodeTexture, it->position.m_x, it->position.m_y, 30, 30);
	}	

	for (Node* node : AIPath)
	{
		if (node != startNode && node != endNode)
		{
			m_spritebatch->DrawSprite(crate, node->position.m_x, node->position.m_y, 30, 30);
		}		
	}

	if (startNode != nullptr)
	{
		m_spritebatch->DrawSprite(mushroom, startNode->position.m_x, startNode->position.m_y, 30, 30);
	}

	if (endNode != nullptr)
	{
		m_spritebatch->DrawSprite(poisonMushroom, endNode->position.m_x, endNode->position.m_y, 30, 30);
	}
	
	player->Draw(m_spritebatch);
	enemy1->Draw(m_spritebatch);

	m_spritebatch->End();
}

void GraphDemo::SetStartNode(Node* node)
{
	startNode = node;
}

//void GraphDemo::ShortenPath(std::list<Node*> path, Node* start)
//{
//	startNode = start;
//}