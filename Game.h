#pragma once

#include "Const.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Wall.h"
#include <iostream>
#include <thread>
#include <mutex>

class Game
{
public:
	Game();
	~Game();

	void RenderThread();
	void PollEvent();
	void Draw();
	void Update();
	void UpdateThread();
	void Run();


	bool Jump;
	bool GameRuning;
	sf::Clock clk;
	float dt;

	sf::RenderWindow window;
	Player player;
	sf::Texture playertext;
	sf::Texture windowtext;
	sf::Texture bg;
	sf::Texture pl;
	sf::RectangleShape background;
	std::vector<Wall> platforms;
};

