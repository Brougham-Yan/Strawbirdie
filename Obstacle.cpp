#include "Obstacle.h"

Obstacle::Obstacle()
{
	speed = 10; //temporary
	speedMultiplier = 100;
	sprite = agk::CreateSprite(0);
	agk::SetSpriteSize(sprite, 50, -1);
	agk::SetSpriteShape(sprite, 2);
	//add depth
	reset(0);
	//set start coordinates
}

Obstacle::~Obstacle()
{
	agk::DeleteSprite(sprite);
}

void Obstacle::update()
{
	xPos -= ((speed * speedMultiplier) / 100);
	agk::SetSpritePosition(sprite, xPos, yPos);
}

int Obstacle::getSprite()
{
	return sprite;
}

void Obstacle::reset()//less than ideal solution, needs either significant tweaking or a full overhaul
{

	xPos = agk::Random(105, 205) * 100;//multiply by a constant to force them to space out
	yPos = agk::Random(0, 10) * 75;

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
}

void Obstacle::reset(int time)//less than ideal solution, needs either significant tweaking or a full overhaul
{
	int multiplier = time / 15;
	int hazardChance = (int)(pow(.9, multiplier) * 100);

	

	xPos = agk::Random(105, 205) * 10;//multiply by a constant to force them to space out
	yPos = agk::Random(0, 72) * 10;

	int i = agk::Random(0, 99);
	if (i > hazardChance)
	{
		type = 1;//hazard
		agk::SetSpriteColor(sprite, 255, 0, 0, 255);
	}
	else if (i < 2)
	{
		type = 2;//health
		agk::SetSpriteColor(sprite, 0, 255, 0, 255);
	}
	else
	{
		type = 0;//regular points
		agk::SetSpriteColor(sprite, 255, 255, 255, 255);
	}
}

int Obstacle::getType()
{
	return type;
}

int Obstacle::getXPos()
{
	return xPos;
}

void Obstacle::setSpeedMultiplier(int i)
{
	speedMultiplier = i;
}