#ifndef GAME_STATE_H

#define GAME_STATE_H

#include "State.h"

class GameState:
	public State
{
private:
	Entity player;


	//Functions
	void initKeybinds();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);

};

#endif