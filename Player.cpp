#include "Player.h"
using namespace AGK;

player::player()
{
	yPos = 250.0;
	xPos = 150.0;
	speed = 5;
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
	//agk::SetSpriteColor(playerSprite, 255, 255, 255, 255);
	agk::SetSpriteDepth(playerSprite, 25);
	health = 3;
	healthDisplay = agk::CreateText("3");
	agk::SetTextSize(healthDisplay, 40);
	agk::SetTextPosition(healthDisplay, 45, 690);
	agk::SetTextDepth(healthDisplay, 5);
	agk::SetTextVisible(healthDisplay, 0);
	invincibleTime = 0;
	velocity = 0;
	//add depth
}

player::~player()
{
	agk::DeleteSprite(playerSprite);
}

void player::update()
{
	//if (agk::GetRawKeyState(40) == 1)//if pressing down
	//	yPos += speed;
	//if (agk::GetRawKeyState(38) == 1)//if pressing up
	//	yPos -= speed;
	//if (agk::GetRawKeyState(37) == 1)//if pressing left
	//	xPos -= (speed / 1.5);
	//if (agk::GetRawKeyState(39) == 1)//if pressing right
	//	xPos += (speed * 1.5);
	if (agk::GetRawKeyState(32) == 1)//if pressing up
		velocity += 0.25;
	else
		velocity -= 0.12;
	//if (agk::GetRawKeyState(39) == 1)//if pressing right
	//	xPos += (speed * 1.5);
	//else
	//	xPos -= (speed / 1.5);
	yPos -= velocity;

	if (yPos < 0)
		velocity = (-velocity*.5) -2;
		//velocity = (-5);
	if (yPos > 768 - size - 50)
		velocity = (-velocity*.5) +2;
		//velocity = 3;
	if (xPos < 150) 
		xPos = 150;
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
	agk::SetSpriteAngle(playerSprite, (velocity*-3));
}

int player::getSprite()
{
	return playerSprite;
}

void player::addPoints(int points)
{
	score += points;
	if (score > 49)//every 50 strawberries, get a health
	{
		score -= 50;
		health++;
	}
}

int player::getScore()
{
	return score;
}

void player::loseHealth(int damage)
{
	health -= damage;
	std::string s = std::to_string(health);
	agk::SetTextString(healthDisplay, s.c_str());
}

void player::gainHealth(int recovery)
{
	health += recovery;
	if (health > 5)
		health = 5;
	std::string s = std::to_string(health);
	agk::SetTextString(healthDisplay, s.c_str());
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
	if (size < 70)
		health = 0;
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

void player::setHealthVisible(int i)
{
	if (i == 1)
		agk::SetTextVisible(healthDisplay, 1);
	else
		agk::SetTextVisible(healthDisplay, 0);
}