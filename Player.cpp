#include "Player.h"
using namespace AGK;

player::player()
{
	yPos = 250.0;
	xPos = 150.0;
	speed = 15;
	agk::CreateSprite(playerSprite, 0);
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/frame-1.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/frame-2.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/frame-3.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/frame-4.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/frame-5.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/frame-6.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/frame-7.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/frame-8.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/hit-frame-1.png"));
	agk::AddSpriteAnimationFrame(playerSprite, agk::LoadImage("/assets/player/hit-frame-2.png"));

	agk::PlaySprite(playerSprite, 10, 1, 1, 8);
	score = 0;
	size = 125;
	agk::SetSpriteSize(playerSprite, size, -1);
	agk::SetSpriteShape(playerSprite, 2);
	agk::SetSpriteColor(playerSprite, 255, 255, 255, 255);
	health = 3;
	invincibleTime = 0;
	//add depth
}

player::~player()
{
	agk::DeleteSprite(playerSprite);
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
	if (invincibleTime > 0)
	{
		if (std::clock() % 5 == 0)//if it's an even frame?
			agk::SetSpriteColor(playerSprite, 255, 255, 255, 0);
		else
			agk::SetSpriteColor(playerSprite, 255, 255, 255, 255);
		if ((std::clock() - timer) / (double)CLOCKS_PER_SEC > 1)//if it's been a second since the last second
		{
			timer == std::clock();
			invincibleTime--;
			agk::SetSpriteColor(playerSprite, 255, 255, 255, 255);
		}
		if (invincibleTime < 1)
			agk::PlaySprite(playerSprite, 10, 1, 1, 8);
	}

	agk::SetSpritePosition(playerSprite, xPos, yPos);
}

int player::getSprite()
{
	return playerSprite;
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

//void player::updateSprite(int i)
//{
//	if (i == 0)
//		agk::SetSpriteColor(playerSprite, 0, 0, 0, 0);
//}

void player::loseSize(int i)
{
	size -= i;
	if (size < 25)
		size = 25;
	agk::SetSpriteSize(playerSprite, size, -1);
}

void player::gainSize(int i)
{
	size +=i;
	agk::SetSpriteSize(playerSprite, size, -1);
}

void player::setInvincible(int time)
{
	agk::PlaySprite(playerSprite, 10, 1, 9, 10);

	invincibleTime = time;
}

int player::getInvincibleTime()
{
	timer = std::clock();
	return invincibleTime;
}