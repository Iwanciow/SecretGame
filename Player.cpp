#include "stdafx.h"
#include "Player.h"


Player::Player():shape({40.f,50.f}), speed(0.f,0.f)
{
	shape.setPosition(0.f, 300.f);
	//shape.setOrigin(20.f, 50.f);
	
	
}

Player::~Player()
{
}



void Player::Draw(sf::RenderWindow &window)
{

	window.draw(shape);
}