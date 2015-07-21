#include "Obstacle.h"

Obstacle::Obstacle()
{
	speed = 5; //temporary
	sprite = agk::CreateSprite(0);
	agk::SetSpriteSize(sprite, 25, -1);
	agk::SetSpriteShape(sprite, 2);
	//add depth
	reset();
	//set start coordinates
}

Obstacle::~Obstacle()
{
	agk::DeleteSprite(sprite);
}

void Obstacle::update()
{
	xPos -= speed;
	if (xPos < -15)
	{
		reset();
	}
	agk::SetSpritePosition(sprite, xPos, yPos);
}

int Obstacle::getSprite()
{
	return sprite;
}

void Obstacle::reset()
{
	int i = agk::Random(0, 99);
	if (i < 30)
	{
		type = 1;
		agk::SetSpriteColor(sprite, 255, 0, 0, 255);
	}
	else{
		type = 0;
		agk::SetSpriteColor(sprite, 0, 255, 0, 255);
	}
	xPos = agk::Random(1050, 2048);
	yPos = agk::Random(0, 718);
}

int Obstacle::getType()
{
	return type;
}

int Obstacle::getXPos()
{
	return xPos;
}