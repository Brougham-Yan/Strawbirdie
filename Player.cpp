#include "Player.h"
using namespace AGK;

player::player()
{
	yPos = 250.0;
	xPos = 150.0;
	speed = 10;
	sprite = agk::CreateSprite(0);
	score = 0;
	size = 125;
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
	if (agk::GetRawKeyState(37) == 1)//if pressing left
		xPos -= (speed / 1.5);
	if (agk::GetRawKeyState(39) == 1)//if pressing right
		xPos += (speed * 1.5);
	if (yPos < 0) 
		yPos = 0;
	if (yPos > 768 - size) 
		yPos = 768 - size;
	if (xPos < 0) 
		xPos = 0;
	if (xPos > 1024 - size) 
		xPos = 1024 - size;
	agk::SetSpritePosition(sprite, xPos, yPos);
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

void player::gainHealth(int recovery)
{
	health += recovery;
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