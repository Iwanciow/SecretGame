#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{


	mbg.loadFromFile("8BitCity.jpg");
	menuBackground.setTexture(&mbg);
	

	if (!font.loadFromFile("AstalametPure.ttf"))
	{
		std::cout << "I can't load font\n";
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f((RESOLUTION_X / 2 )-50, RESOLUTION_Y/ (MAX_NUBER_OF_ITEMS + 1)* 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Button");
	menu[1].setPosition(sf::Vector2f((RESOLUTION_X / 2)-50, RESOLUTION_Y / (MAX_NUBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f((RESOLUTION_X / 2)-50, RESOLUTION_Y / (MAX_NUBER_OF_ITEMS + 1) * 3));
	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow & window)
{
	menuBackground.setSize(sf::Vector2f(RESOLUTION_X, RESOLUTION_Y));
	window.draw(menuBackground);
	for (int i = 0; i < MAX_NUBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}

}

void Menu::Up()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}

void Menu::Down()
{
	if (selectedItemIndex + 1 <= MAX_NUBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}



