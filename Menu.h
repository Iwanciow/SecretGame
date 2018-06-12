#pragma once
#include "Const.h"

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Wall.h"
#include <iostream>
class Menu
{
public:
	
	Menu();
	~Menu();

	void draw(sf::RenderWindow &widnow);
	void Up();
	void Down();
	int state;
	int GetPressedItem() { return selectedItemIndex; }
	int selectedItemIndex;
private:
	
	sf::Texture mbg;
	sf::RectangleShape menuBackground;
	sf::Font font;
	sf::Text menu[MAX_NUBER_OF_ITEMS];

};

