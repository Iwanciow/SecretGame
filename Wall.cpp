#include "stdafx.h"
#include "Wall.h"


Wall::Wall(sf::Vector2f pos, sf::Vector2f size, sf::Texture &texture):platform(size)
{
	platform.setPosition(pos);
	platform.setTexture(&texture);
}


Wall::~Wall()
{
}

void Wall::draw(sf::RenderWindow &window)
{

	window.draw(platform);

}
bool Wall::colisionTop(sf::FloatRect rect)
{
	sf::Vector2f coordsPlayerBottomL(rect.left, rect.top + rect.height);
	sf::Vector2f coordsPlayerBottomR(rect.left + rect.width, rect.top + rect.height);
	sf::Vector2f platformTopL(platform.getGlobalBounds().left, platform.getGlobalBounds().top);
	sf::Vector2f platformTopR(platform.getGlobalBounds().left + platform.getGlobalBounds().width, platform.getGlobalBounds().top);




	if (coordsPlayerBottomL.x >= platformTopL.x  && coordsPlayerBottomL.x <= platformTopR.x)
	{
		
		if (coordsPlayerBottomL.y >= platformTopL.y && 
			coordsPlayerBottomR.y <= platformTopR.y + platform.getGlobalBounds().height)
		{
			return true;
		}
	}
	if (coordsPlayerBottomR.x >= platformTopL.x  && coordsPlayerBottomR.x <= platformTopR.x)
	{
		if (coordsPlayerBottomL.y >= platformTopL.y && 
			coordsPlayerBottomR.y <= platformTopR.y + platform.getGlobalBounds().height)
		{
			return true;
		}
	}
	return false;

}

bool Wall::colisionBottom(sf::FloatRect rect)
{
	sf::Vector2f coordsPlayerTopL(rect.left, rect.top);
	sf::Vector2f coordsPlayerTopR(rect.left + rect.width, rect.top);
	sf::Vector2f platformBottomL(platform.getGlobalBounds().left, platform.getGlobalBounds().top +platform.getGlobalBounds().height);
	sf::Vector2f platformBottomR(platform.getGlobalBounds().left + platform.getGlobalBounds().width, platform.getGlobalBounds().top + platform.getGlobalBounds().height);




	if (coordsPlayerTopL.x >= platformBottomL.x  && coordsPlayerTopL.x <= platformBottomR.x)
	{

		if (coordsPlayerTopL.y <= platformBottomL.y &&
			coordsPlayerTopR.y >= platformBottomR.y - platform.getGlobalBounds().height)
		{
			return true;
		}
	}
	if (coordsPlayerTopR.x >= platformBottomL.x  && coordsPlayerTopR.x <= platformBottomR.x)
	{
		if (coordsPlayerTopL.y <= platformBottomL.y &&
			coordsPlayerTopR.y >= platformBottomR.y - platform.getGlobalBounds().height)
		{
			return true;
		}
	}
	return false;
}

bool Wall::colision_l(sf::FloatRect rect)
{
	sf::Vector2f coordsPlayerBottomR(rect.left + rect.width, rect.top + rect.height);
	sf::Vector2f coordsPlayerTopR(rect.left + rect.width, rect.top);
	sf::Vector2f platformBottomL(platform.getGlobalBounds().left -1 , platform.getGlobalBounds().top + platform.getGlobalBounds().height);
	sf::Vector2f platformTopL(platform.getGlobalBounds().left  -1 , platform.getGlobalBounds().top);

	if ((coordsPlayerTopR.y < platformBottomL.y && coordsPlayerTopR.y > platformTopL.y) ||
		(coordsPlayerBottomR.y < platformBottomL.y && coordsPlayerBottomR.y > platformTopL.y))
	{

		if (coordsPlayerBottomR.x >= platformBottomL.x  &&
			coordsPlayerBottomR.x <= platformBottomL.x + 10.f)
		{
			return true;
		}
		
	}


	return false;
}
bool Wall::colision_r(sf::FloatRect rect)
{
	sf::Vector2f coordsPlayerBottomL(rect.left, rect.top + rect.height);
	sf::Vector2f coordsPlayerTopL(rect.left, rect.top);
	sf::Vector2f platformBottomR(platform.getGlobalBounds().left + platform.getGlobalBounds().width + 1, platform.getGlobalBounds().top + platform.getGlobalBounds().height);
	sf::Vector2f platformTopR(platform.getGlobalBounds().left + platform.getGlobalBounds().width + 1, platform.getGlobalBounds().top);

	if ((coordsPlayerTopL.y < platformBottomR.y && coordsPlayerTopL.y > platformTopR.y) ||
		(coordsPlayerBottomL.y < platformBottomR.y && coordsPlayerBottomL.y > platformTopR.y))
	{

		if (coordsPlayerBottomL.x <= platformBottomR.x  &&
			coordsPlayerBottomL.x >= platformBottomR.x - 10.f)
		{
			return true;
		}

	}
	return false;
}
// Sprawdzanie kolizji elo
void Wall::chColision(Player & player)
{
	
	if (colisionTop(player.shape.getGlobalBounds()))
	{
		if (player.speed.y > 0.0f)
		{


			player.speed.y = 0.f;
		}

	}
	else if (colisionBottom(player.shape.getGlobalBounds()))
	{
		if (player.speed.y < 0.0f)
		{


			player.speed.y = 0.f;
		}
	}

	if (colision_l(player.shape.getGlobalBounds()))
	{
		if (player.speed.x > 0.0F)
		{
			player.speed.x = -1.0f;
		}

	}
	else if (colision_r(player.shape.getGlobalBounds()))
	{
		if (player.speed.x < 0.0F)
		{
			player.speed.x = +1.0f;
		}
	}


}


