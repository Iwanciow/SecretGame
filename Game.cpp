#include "stdafx.h"
#include "Game.h"

#include <Windows.h>


Game::Game():window(sf::VideoMode(RESOLUTION_X, RESOLUTION_Y), WIN_NAME, sf::Style::Close | sf::Style::Titlebar)
{
	

	window.setFramerateLimit(60);
	playertext.loadFromFile("player.png");
	player.shape.setTexture(&playertext);
	bg.loadFromFile("could.png");
	background.setTexture(&bg);
	pl.loadFromFile("platform.png");
	
	
	
	platforms.push_back(Wall({ -10,RESOLUTION_Y-20 }, { RESOLUTION_X+10,30 }, pl));	//platforma dol
	platforms.push_back(Wall({ -10,0 }, { 10, RESOLUTION_Y },pl)); //platforma lewo
	platforms.push_back(Wall({ RESOLUTION_X,0} , { 10,RESOLUTION_Y },pl));	//platforma prawo
	platforms.push_back(Wall({ 250,625 }, { 90,45 },pl));
	platforms.push_back(Wall({ 400,565 }, { 90,45 },pl));
	platforms.push_back(Wall({ 550,535 }, { 90,45 },pl));
	platforms.push_back(Wall({ 650,470 }, { 110,45 },pl));
	platforms.push_back(Wall({ 450,400 }, { 90,40 }, pl));
	
	background.setSize(sf::Vector2f(RESOLUTION_X, RESOLUTION_Y));
	menu.state = 0;
	
}


Game::~Game()
{
}

void Game::Display() {

	while (window.isOpen()) {

		if (menu.state == 0) {

			MenuUpdate();
			DrawMenu();
		}


		if (menu.state == 1) {


			PollEvent();
			Update();
			Draw();
		}

		if (menu.state == 2) {


		}

	}
}


void Game::PollEvent() {


	sf::Event event;
	while (window.pollEvent(event))
	{


		//closed window
		if (event.type == sf::Event::Closed)
			window.close();
		//closed window ESC
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			menu.state = 0;


		//show position
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::RShift)
		{
			std::cout << "Checking position" << std::endl;
			std::cout << "X position = " << player.shape.getPosition().x << std::endl;
			std::cout << "Y position = " << player.shape.getPosition().y << "\n\n";
		}
		//don't change resolution
		else if (event.type == sf::Event::Resized)
			window.setSize(sf::Vector2u(RESOLUTION_X, RESOLUTION_Y));
	}


	switch (event.type)
	{
	case sf::Event::KeyReleased: {
		switch (event.key.code)
		{
		case sf::Keyboard::Space: //jump
		{
			if (player.speed.y == 0)
			{
				player.speed += {0.f, -9.f};
				if (player.speed.y < -9.f)
				{
					player.speed.y = -9.f;
				}
				jump = true;
			}
			break;
		}
		case sf::Keyboard::Return: //reset position
		{
			player.shape.setPosition(300, 300);
			break;
		}
		}
		break;
	}
	}


}


void Game::Update()
{
	bool moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.shape.getPosition().x > 0 )
	{
		player.speed += {-0.95f, 0.f};
		if (player.speed.x < -6.f)
		{
			player.speed.x = -6.f;
		}
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.shape.getPosition().x + player.shape.getSize().x < window.getSize().x)
	{
		player.speed += {0.95f, 0.f};
		
		if (player.speed.x > 6.f)
		{
			player.speed.x = 6.f;
		}
		moving = true;
	}

	if (!moving) {
		if (player.speed.x < -1)
			player.speed.x += 1.0f;
		else if (player.speed.x > 1)
			player.speed.x -= 1.f;
		else
			player.speed.x = 0.f;
		moving = false;
	}
	/*######################################################
	
						Gravitation
	
	########################################################*/
		player.speed += {0.f, 0.5f};
		
		if (player.speed.y > 10.f)
		{
			player.speed.y = 10.f;
		}
	
	
	//iterator do vektora
	for (auto iter = platforms.begin(); iter != platforms.end(); iter++) {
		iter->chColision(player);
	}

	

	player.shape.move(player.speed);

}

void Game::MenuUpdate()
{
	sf::Event EventMenu;
	while (window.pollEvent(EventMenu))
	{
		if (EventMenu.type == sf::Event::KeyPressed && EventMenu.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}

		if (EventMenu.type == sf::Event::Closed)
			window.close();

		switch (EventMenu.type)
		{
		case sf::Event::KeyReleased: {
			switch (EventMenu.key.code)
			{
			case sf::Keyboard::W:
			{
				std::cout << "W is pressed\n";
				menu.Up();
				break;
			}
			case sf::Keyboard::S:
			{
				std::cout << "S is pressed\n";
				menu.Down();
				break;
			}
			case sf::Keyboard::Return:
				std::cout << "Enter is pressed\n";
				switch (menu.GetPressedItem())
				{
				case 0:
				{

					menu.state = 1;
					break;
				}
				case 1:
				{
					menu.state = 0;
					break;
				}
				case 2:
				{
					window.close();
					break;
				}
					break;
				}
				break;
			}
			break;
		}
		}
	}
}

void Game::Draw() {

	window.clear(sf::Color::White);
	
	
	window.draw(background);
	for (auto iter = platforms.begin(); iter != platforms.end(); iter++) {
		iter->draw(window);
	}
	player.Draw(window);
	
	window.display();

}

void Game::DrawMenu()
{
	window.clear(sf::Color::White);
	menu.draw(window);

	window.display();

}

