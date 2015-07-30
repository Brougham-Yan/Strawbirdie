#include "Obstacle.h"

Obstacle::Obstacle()
{
	speed = 15; //temporary
	speedMultiplier = 100;
	sprite = agk::CreateSprite(0);
	strawberry = agk::LoadImage("/assets/hazards/strawberry.png");
	popsicle = agk::LoadImage("assets/hazards/cherry.png");
	enemy = agk::LoadImage("assets/hazards/frame-1.png");
	agk::SetSpriteSize(sprite, 50, -1);
	agk::SetSpriteShape(sprite, 2);
	//add depth
	reset(0);
	//set start coordinates
}

Obstacle::Obstacle(int s)
{
	speed = s; //temporary
	speedMultiplier = 100;
	sprite = agk::CreateSprite(0);
	strawberry = agk::LoadImage("/assets/hazards/strawberry.png");
	popsicle = agk::LoadImage("assets/hazards/cherry.png");
	enemy = agk::LoadImage("assets/hazards/frame-1.png");
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

//void Obstacle::reset()//less than ideal solution, needs either significant tweaking or a full overhaul
//{
//
//	xPos = agk::Random(105, 205) * 100;//multiply by a constant to force them to space out
//	yPos = agk::Random(0, 10) * 75;
//
//	int i = agk::Random(0, 99);
//	if (i < 30)
//	{
//		type = 1;
//		agk::SetSpriteColor(sprite, 255, 0, 0, 255);
//	}
//	else{
//		type = 0;
//		agk::SetSpriteColor(sprite, 0, 255, 0, 255);
//	}
//}

void Obstacle::reset(int time)//less than ideal solution, needs either significant tweaking or a full overhaul
{
	int multiplier = time / 12;
	int hazardChance = (int)(pow(.9, multiplier) * 100);
	agk::DeleteSprite(sprite);
	

	xPos = agk::Random(18, 36) * 60;//multiply by a constant to force them to space out
	yPos = (agk::Random(0, 11) * 60) + 30;

	int i = agk::Random(0, 99);
	if (i > hazardChance)
	{
		sprite = agk::CreateSprite(enemy);
		agk::SetSpriteSize(sprite, 100, -1);
		agk::SetSpriteFlip(sprite, 1, 0);
		type = 1;//hazard
		xPos = agk::Random(11, 22) * 125;
		yPos = agk::Random(0, 4) * 125 + 25;
		speed = (speed * 1.5);
	}
	else if (i < 2)
	{
		sprite = agk::CreateSprite(popsicle);
		agk::SetSpriteSize(sprite, 50, -1);
		type = 2;//health
		xPos = agk::Random(15, 30) * 75;
		yPos = agk::Random(0, 7) * 75 + 10;
	}
	else
	{
		sprite = agk::CreateSprite(strawberry);
		agk::SetSpriteSize(sprite, 75, -1);
		type = 0;//regular points
		xPos = agk::Random(11, 22) * 100;
		yPos = agk::Random(0, 5) * 100 + 20;
		
	}
	agk::SetSpritePosition(sprite, xPos, yPos);

}

void Obstacle::reset(int time, int s)
{
	speed = s;
	reset(time);
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

void Obstacle::setDisabled()
{
	type = -1;//not in use
	agk::SetSpriteColor(sprite, 0, 0, 0, 0);
}

void Obstacle::setDepth(int i)
{
	agk::SetSpriteDepth(sprite, i);
}