#include "Player.h"
using namespace AGK;

player::player()
{
	yPos = 250.0;
	speed = 5;
	sprite = agk::CreateSprite(0);
	score = 0;
	size = 100;
	agk::SetSpriteSize(sprite, size, -1);
	agk::SetSpriteShape(sprite, 2);
	health = 3;
	//add depth
}

player::~player()
{
	agk::DeleteSprite(sprite);
}

void player::update()
{
	if (agk::GetRawKeyState(40) == 1)//if pressing down
		yPos += speed;
	if (agk::GetRawKeyState(38) == 1)//if pressing up
		yPos -= speed;
	if (yPos < 0) yPos = 0;
	if (yPos > 718) yPos = 718;
	agk::SetSpritePosition(sprite, 150.0, yPos);
}

int player::getSprite()
{
	return sprite;
}

void player::addPoints(int points)
{
	score += points;
}

int player::getScore()
{
	return score;
}

void player::loseHealth(int damage)
{
	health -= damage;
}

int player::getHealth()
{
	return health;
}

void player::updateSprite(int i)
{
	if (i == 0)
		agk::SetSpriteColor(sprite, 0, 0, 0, 0);
}

void player::loseSize(int i)
{
	size -= i;
	if (size < 25)
		size = 25;
	agk::SetSpriteSize(sprite, size, -1);
}

void player::gainSize(int i)
{
	size +=i;
	agk::SetSpriteSize(sprite, size, -1);
}