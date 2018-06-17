#pragma once


#include "Const.h"
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();

	void Draw(sf::RenderWindow &window);

	sf::Vector2f speed;
	sf::RectangleShape shape;


	

};

