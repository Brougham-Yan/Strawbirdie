#include "Obstacle.h"

Obstacle::Obstacle()
{
	speed = 15; //temporary
	speedMultiplier = 100;
	sprite = agk::CreateSprite(0);
	strawberry = agk::LoadImage("/assets/hazards/strawberry.png");
	popsicle = agk::LoadImage("assets/hazards/cherry.png");
	enemy = agk::LoadImage("assets/hazards/frame-1.png");
	cloud = agk::LoadImage("assets/hazards/cloud.png");
	agk::SetSpriteSize(sprite, 50, -1);
	agk::SetSpriteShape(sprite, 2);
	//add depth
	reset(0);
	//set start coordinates
}

Obstacle::Obstacle(int s)
{
	speed = s;
	speedMultiplier = 100;
	sprite = agk::CreateSprite(0);
	strawberry = agk::LoadImage("/assets/hazards/strawberry.png");
	popsicle = agk::LoadImage("assets/hazards/cherry.png");
	enemy = agk::LoadImage("assets/hazards/frame-1.png");
	cloud = agk::LoadImage("assets/hazards/cloud.png");
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
	int alpha = agk::GetSpriteColorAlpha(sprite);
	if (alpha < 254 && type != -1)
	{
		alpha += 5;
		agk::SetSpriteColorAlpha(sprite, alpha);
	}

	xPos -= (speed * speedMultiplier / 100);
	agk::SetSpritePosition(sprite, xPos, yPos);
}

int Obstacle::getSprite()
{
	return sprite;
}
void Obstacle::reset(int time)//less than ideal solution, needs either significant tweaking or a full overhaul
{
	setDepth(50);
	notColliding = false;
	int multiplier = time / 12;
	int hazardChance = (int)(pow(.9, multiplier) * 100);
	agk::DeleteSprite(sprite);


	xPos = agk::Random(1024, 2048);//multiply by a constant to force them to space out

	int i = agk::Random(0, 99);
	if (i > hazardChance)
	{
		if (agk::Random(0, 9) > 6)
		{
			sprite = agk::CreateSprite(cloud);
			agk::SetSpriteSize(sprite, 150, -1);
			yPos = agk::Random(0, 450);
			speed += (agk::Random(-1, 1));
			type = 3;//cloud
		}
		else
		{
			sprite = agk::CreateSprite(enemy);
			agk::SetSpriteSize(sprite, 100, -1);
			agk::SetSpriteFlip(sprite, 1, 0);
			type = 1;//hazard
			yPos = agk::Random(0, 525);
			speed = (speed * 1.5);
		}
	}
	else if (i < 2)
	{
		sprite = agk::CreateSprite(popsicle);
		agk::SetSpriteSize(sprite, 50, -1);
		type = 2;//health
		yPos = agk::Random(0, 560);
	}
	else
	{
		sprite = agk::CreateSprite(strawberry);
		agk::SetSpriteSize(sprite, 75, -1);
		type = 0;//regular points
		yPos = agk::Random(0, 550);

	}
	agk::SetSpritePosition(sprite, xPos, yPos);

}

//void Obstacle::reset(int time)//less than ideal solution, needs either significant tweaking or a full overhaul
//{
//	setDepth(50);
//	notColliding = false;
//	int multiplier = time / 12;
//	int hazardChance = (int)(pow(.9, multiplier) * 100);
//	agk::DeleteSprite(sprite);
//	
//
//	xPos = agk::Random(18, 36) * 60;//multiply by a constant to force them to space out
//	yPos = (agk::Random(0, 11) * 60) + 30;
//
//	int i = agk::Random(0, 99);
//	if (i > hazardChance)
//	{
//		if (agk::Random(0, 9) > 6)
//		{
//			sprite = agk::CreateSprite(cloud);
//			agk::SetSpriteSize(sprite, 150, -1);
//			agk::SetSpriteShape(sprite, 2);
//			yPos = agk::Random(0, 3) * 175 + 40;
//			xPos = agk::Random(6, 10) * 200;
//			speed += (agk::Random(-1, 1));
//			type = 3;//cloud
//		}
//		else
//		{
//			sprite = agk::CreateSprite(enemy);
//			agk::SetSpriteSize(sprite, 100, -1);
//			agk::SetSpriteFlip(sprite, 1, 0);
//			agk::SetSpriteShape(sprite, 1);
//			type = 1;//hazard
//			xPos = agk::Random(11, 22) * 125;
//			yPos = agk::Random(0, 4) * 125 + 25;
//			speed = (speed * 1.5);
//		}
//	}
//	else if (i < 2)
//	{
//		sprite = agk::CreateSprite(popsicle);
//		agk::SetSpriteSize(sprite, 50, -1);
//		agk::SetSpriteShape(sprite, 2);
//		type = 2;//health
//		xPos = agk::Random(15, 30) * 75;
//		yPos = agk::Random(0, 7) * 75 + 10;
//	}
//	else
//	{
//		sprite = agk::CreateSprite(strawberry);
//		agk::SetSpriteSize(sprite, 75, -1);
//		agk::SetSpriteShape(sprite, 2);
//		type = 0;//regular points
//		xPos = agk::Random(11, 22) * 100;
//		yPos = agk::Random(0, 5) * 100 + 20;
//		
//	}
//	agk::SetSpritePosition(sprite, xPos, yPos);
//
//}

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
	if (type != 1)
		agk::SetSpriteColor(sprite, 255, 255, 255, 0);
	type = -1;//not in use
}

void Obstacle::setDepth(int i)
{
	agk::SetSpriteDepth(sprite, i);
}

void Obstacle::cloudCover()
{
	type = 9;//expanded cloud
	yPos = 10;
	agk::SetSpriteSize(sprite, -1, 700);
	agk::SetSpriteColorAlpha(sprite, 0);
	speed -= 2;
	setDepth(9);
	update();
}

void Obstacle::setColliding(bool b)
{
	notColliding = b;
}

bool Obstacle::getColliding()
{
	return notColliding;
}