#pragma once
#include <SFML\Graphics.hpp>
#include "Const.h"
#include "Player.h"
class Wall
{
public:
	Wall(sf::Vector2f pos, sf::Vector2f size,sf::Texture &texture);
	~Wall();

	sf::RectangleShape platform;

	void draw(sf::RenderWindow &window);
	bool colisionTop(sf::FloatRect rect);
	bool colisionBottom(sf::FloatRect rect);
	bool colision_l(sf::FloatRect rect);
	bool colision_r(sf::FloatRect rect);
	void chColision(Player &player);

	void setTexture(sf::Texture &texture) { 
		platform.setTexture(&texture); 
	};

};
