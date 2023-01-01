#include "MainMenuBackground.h"

MainMenuBackground::MainMenuBackground()
{
}

MainMenuBackground::~MainMenuBackground()
{
}

void MainMenuBackground::Initialise()
{
	background.Initialise("sprites/backgroundColour.png");
}

void MainMenuBackground::Update()
{
	background.setScale(50, 50);
	background.setPosition(-500, -500);
}

sf::Vector2f MainMenuBackground::GetPosition()
{
	return background.getPosition();
}

void MainMenuBackground::SetPosition(float px, float py)
{
	background.setPosition(px, py);
}

void MainMenuBackground::SetPosition(sf::Vector2f ppos)
{
	background.setPosition(ppos);
}

void MainMenuBackground::GetPosition(float& x, float& y)
{
	x = background.getPosition().x;
	y = background.getPosition().y;

}
