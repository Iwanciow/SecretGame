#pragma once

#include "Const.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Wall.h"
#include <iostream>


class Game
{
public:
	Game();
	~Game();

	void Display();
	void PollEvent();
	void Draw();
	void DrawMenu();
	void Update();
	void MenuUpdate();

	
	
	sf::RenderWindow window;
	Menu menu;
private:
	
	bool jump;
	Player player;
	sf::Texture playertext;
	sf::Texture windowtext;
	sf::Texture bg;
	sf::Texture pl;
	
	sf::RectangleShape background;
	
	std::vector<Wall> platforms;
};

