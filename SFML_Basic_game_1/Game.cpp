#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endgame = false;
	this->points = 0;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHold = false;
}

void Game::initwindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;

	this->window = new sf::RenderWindow(this->videomode, "sfml tutorial", sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(60);

}

void Game::initFont()
{
	if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::GAME::INIFONTS::Falied to load font!" << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);

}

void Game::initenemy()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);



}

Game::Game()
{
	this->initVariables();
	this->initwindow();
	this->initenemy();
	this->initText();
	this->initFont();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endgame;
}

//Functions

void Game::spawnEnemy()
{
	/*
		@return void

		Spawn enemies and sets their colors, types and positions randomly.
		-Sets a random position.
		-Sets a random color.
		-Adds enemy to the vector.
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	int type = rand() % 5;
	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break; 
	case 3:
			this->enemy.setSize(sf::Vector2f(70.f, 70.f));
			this->enemy.setFillColor(sf::Color::Red);
			break;
	case 4:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;

	default:
		this->enemy.setSize(sf::Vector2f(150.f, 150.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;


	}

	this->enemies.push_back(this->enemy);

}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
	@ return void

	Updates the mouse positions
		 -Mouse positions relative to window (Vecotor2i)
	*/
	
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n";

	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	/*
	    @return void

		Updates the enemy spawn timer and spawns enemies .
		when the total amount of enemies is smaller than the maximum.
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen 
	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move and updatind the enemies
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		

		this->enemies[i].move(0.f, 5.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health<< "\n";
		}
	}
	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHold == false)
		{
			this->mouseHold = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{

					//Gain points
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 7;
					if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 5;
					if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 3;
					if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;

					std::cout << "Points :" << this->points << "\n";

					//delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
		else
		{
			this->mouseHold = false;
		}
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->endgame == false)
	{
		this->updateMousePositions();
		
		this->updateText();

		this->updateEnemies();
	}
	//endgame condition
	if (this->health <= 0)
	{
		this->endgame = true;
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	/*
		#return void

		- clear old frame
		- render objects
		- display frame in window

	  Renders the game objects

	*/

	this->window->clear();

	//Draw game objects
	this->renderEnemies(*this->window);

	this->renderText(*this->window);
	this->window->display();
}