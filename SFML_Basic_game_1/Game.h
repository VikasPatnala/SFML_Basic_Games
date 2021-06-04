#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game
{
private:
	// Variable and Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources 
	sf::Font font;

	//Text 
	sf::Text uiText;

	//Game logic
	unsigned points;
	bool endgame;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHold;

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;


	// Private functions
	void initVariables();
	void initwindow();
	void initFont();
	void initText();
	void initenemy();

public:
	//Constructors /Destructors
	Game();
	virtual ~Game();
	
	//Accessors
	const bool running() const; 
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();


};