#include "stdafx.h"
#include "Game.h"
#include <Windows.h>


Game::Game():window(sf::VideoMode(RESOLUTION_X, RESOLUTION_Y), WIN_NAME, sf::Style::Close | sf::Style::Titlebar)
{
	GameRuning = true;
	playertext.loadFromFile("player.png");
	player.shape.setTexture(&playertext);
	bg.loadFromFile("could.png");
	background.setTexture(&bg);
	pl.loadFromFile("platform.png");
	
	
	platforms.push_back(Wall({ -10,RESOLUTION_Y-2 }, { RESOLUTION_X+10,30 }, pl));	//platforma dol
	//platforms.push_back(Wall({ -10,0 }, { 10, RESOLUTION_Y },pl)); //platforma lewo
	//platforms.push_back(Wall({ RESOLUTION_X,0} , { 10,RESOLUTION_Y },pl));	//platforma prawo
	platforms.push_back(Wall({ 350,400 }, { 100,60 },pl));
	platforms.push_back(Wall({ 200,100 }, { 100,60 },pl));
	platforms.push_back(Wall({ 200,300 }, { 100,60 },pl));
	
	
	background.setSize(sf::Vector2f(RESOLUTION_X, RESOLUTION_Y));
	
	
}


Game::~Game()
{
}

void Game::RenderThread() {
	window.setFramerateLimit(60);
	
	while (window.isOpen())
	{
	
		
		Draw();
	}

}

void Game::PollEvent() {


	sf::Event event;
	while (window.pollEvent(event))
	{


		//closed window
		if (event.type == sf::Event::Closed)
		{
			GameRuning = false;
			window.close();
			
		}
		//closed window ESC
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			GameRuning = false;
			window.close();
		}

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
			player.speed += {0.f, -200.f * dt};
			Jump = true;
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
		player.speed += {-10.f *dt, 0.f};
		if (player.speed.x < -1000.f*dt)
		{
			player.speed.x = -1000.f *dt;
		}
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.shape.getPosition().x + player.shape.getSize().x < window.getSize().x)
	{
		player.speed.x += 10.0f * dt;
		
		if (player.speed.x > 1000.f*dt)
		{
			player.speed.x = 1000.f*dt;
		}
		moving = true;
	}

	if (!moving) {
		if (player.speed.x < -1*dt)
			player.speed.x += 1.0f * dt;
		else if (player.speed.x > 1*dt)
			player.speed.x -= 1.f * dt;
		else
			player.speed.x = 0.f *dt;
		moving = false;
	}
	/*######################################################
	
						GRAWITACJA
	
	########################################################*/
		player.speed.y += 0.50f *dt;
		
		if (player.speed.y > 200.f *dt)
		{
			player.speed.y = 200.f * dt;
		}

		else if (player.speed.y < -200.f *dt)
		{
			player.speed.y = -200.f*dt;
		}

	
	
	//iterator do vektora
	for (auto iter = platforms.begin(); iter != platforms.end(); iter++) {
		iter->chColision(player,dt);
	}


	player.shape.move(player.speed);

}

void Game::UpdateThread()
{
	
	while (GameRuning)
	{
		dt = clk.restart().asSeconds();

		PollEvent();
		Update();
		
	}
}

void Game::Run()
{
	window.setActive(false);
	std::thread renderthread(&Game::RenderThread, this);

	UpdateThread();
	
	renderthread.join();
	this->window.close();

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
