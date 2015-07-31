// Includes
#include "main.h"
#include "Player.h"
#include "Obstacle.h"
#include "Background.h"
#include "Score.h"
#include <ctime>
// Namespace
using namespace AGK;

app App;
const int numberObstacles = 5; //number of obstacles allowed on screen at once; 
float Aspect = 0.0;
player *p1;
background *bg;
Obstacle *obstacles[numberObstacles];
Score *scoreBoard;
int gameMode = 0;//what gamemode you're in
std::clock_t start;//start time of each day
double duration;//duration of the day
int dayLength = 60;//seconds in each day
int timeRemaining;
int lastTick = 0;
int speed = 10;
int speedMultiplier = 100;
//int finalScore = 0;

int selection;//used in menus and such

void app::Begin(void)
{
	Aspect = ((float)agk::GetDeviceWidth() / agk::GetDeviceHeight());
	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);//max FPS?
	agk::SetScissor(0,0,0,0);//???
	agk::SetRandomSeed(agk::GetMilliseconds()); //seed the RNG based on system clock
	selection = 0;
	bg = new background();
	scoreBoard = new Score();
}

void app::Loop (void)
{
	agk::Print(agk::ScreenFPS());
	switch (gameMode)
	{
	case 0://main menu
		agk::Print("Main Menu");
		switch (selection)
		{
		case 0:
			agk::Print("Press space to start");
			if (agk::GetRawKeyPressed(32) == 1)
			{
				newGame(1);
				selection = 0;
			}
			break;
		case 1:
			agk::Print("Press space for endless mode");
			if (agk::GetRawKeyPressed(32) == 1)
			{
				duration = 0.0f;
				newGame(5);
				selection = 0;
			}
			break;
		case 2:
			agk::Print("Press space for high scores");
			if (agk::GetRawKeyPressed(32) == 1)
			{
				selection = 0;
				gameMode = 6;
			}
			break;
		case 3:
			agk::Print("Press space for options");
			if (agk::GetRawKeyPressed(32) == 1)
			{
				gameMode = 4;
				selection = 0;
			}
			break;
		}

		if (agk::GetRawKeyPressed(38) == 1)
			selection--;
		if (agk::GetRawKeyPressed(40) == 1)
			selection++;
		if (selection < 0)
			selection = 3;
		else if (selection > 3)
			selection = 0;

		break;

	case 1://normal game
		p1->update();
		for (int i = 0; i < numberObstacles; i++)
		{
			obstacles[i]->update();
		}
		CheckCollisions();
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		timeRemaining = dayLength - (int)duration;
		if (timeRemaining < 0)
		{
			gameMode = 2;
			//some sort of function here
		}
		agk::Print(timeRemaining);
		agk::Print(p1->getScore());
		agk::Print(p1->getHealth());

		break;
	case 2:
		agk::Print("Day Over");
		break;
	case 3:
		agk::Print("Game Over");
		agk::Print(scoreBoard->getPoints());
		agk::Print("Press space to return to the main menu");
		if (agk::GetRawKeyPressed(32) == 1)
			gameMode = 0;
		break;
	case 4://options
		agk::Print("Options");
		switch (selection)
		{
		case 0:
			agk::Print("Press space to return to the main menu");
			if (agk::GetRawKeyPressed(32) == 1)
			{
				selection = 0;
				gameMode = 0;
			}
			break;
		case 1:
			agk::Print("speed multiplier:");
			agk::Print(speedMultiplier);
			if (agk::GetRawKeyPressed(39) == 1)//right arrow
				speedMultiplier += 10;
			else if (agk::GetRawKeyPressed(37) == 1)//left arrow
				speedMultiplier -= 10;
			break;
		}
		if (agk::GetRawKeyPressed(38) == 1)
			selection--;
		else if (agk::GetRawKeyPressed(40) == 1)
			selection++;
		if (selection < 0)
			selection = 1;
		else if (selection > 1)
			selection = 0;
		break;
	case 5://endless
		if (selection == 0)//not paused
		{
			p1->update();
			for (int i = 0; i < numberObstacles; i++)
			{
				obstacles[i]->update();
			}
			CheckCollisions();

			if ( (std::clock() - start) / (double)CLOCKS_PER_SEC > 1)//if it's been a second since the last second
			{
				duration++;
				start = std::clock();
				p1->loseSize(1);
			}
			agk::Print((int)duration);
			agk::Print(p1->getScore());
			agk::Print(p1->getHealth());
			if (agk::GetRawKeyPressed(27) == 1)//escape pressed
				selection = 1;
		}
		else{
			if (agk::GetRawKeyPressed(27) == 1)//escape pressed
			{
				selection = 0;
				start = std::clock();
			}
			agk::Print("Paused");
		}
			break;
	case 6://high scores
	{
		scoreBoard->displayScores();
		if (agk::GetRawKeyPressed(32) == 1)
			gameMode = 0;
		break;
	}
	}
	bg->update();
	agk::Sync();
}


void app::End (void)
{

}

void app::CheckCollisions()
{
	for (int i = 0; i < numberObstacles; i++)
	{
		if (obstacles[i]->getColliding() == false)//if the obstacle hasn't been confirmed to be not colliding
		{
			obstacles[i]->setColliding(true);
			for (int j = 0; j < numberObstacles; j++)
			{
				if (obstacles[i]->getColliding() == true && i != j)
				{
					if (agk::GetSpriteCollision(obstacles[i]->getSprite(), obstacles[j]->getSprite()) == true)//if it's colliding
						obstacles[i]->reset((int)duration, speed);
				}
			}
		}
		if (obstacles[i]->getXPos() < -100 && obstacles[i] ->getType() != 9)
		{
			obstacles[i]->setDepth(i + 50);
			obstacles[i]->reset((int)duration, speed);
		}
		else if (obstacles[i]->getXPos() < -1500)
		{
			obstacles[i]->setDepth(i + 50);
			obstacles[i]->reset((int)duration, speed);
		}
		if (obstacles[i]->getType() != -1)
		{
			if (agk::GetSpriteCollision(p1->getSprite(), obstacles[i]->getSprite()) == true && obstacles[i] ->getType() !=9)
			{
				if (obstacles[i]->getType() == 0)
				{
					scoreBoard->addPoints(1);
					p1->addPoints(1);
					obstacles[i]->setDisabled();
					if (gameMode == 5)
						p1->gainSize(3);
					return;
				}
				else if (obstacles[i]->getType() == 1 && p1->getInvincibleTime() < 1){
					p1->loseHealth(1);
					p1->setInvincible(1);
					obstacles[i]->setDisabled();
					if (p1->getHealth() < 1)
					{
						gameOver();
					}
					return;
				}
				else if (obstacles[i]->getType() == 2)
				{
					p1->gainHealth(1);
					obstacles[i]->setDisabled();
					return;
				}
				else if (obstacles[i]->getType() == 3)
				{
					obstacles[i]->cloudCover();
					return;
				}
			}
		}
	}
}

void app::newGame(int i)
{
	p1 = new player();

	for (int i = 0; i < numberObstacles; i++)
	{
		obstacles[i] = new Obstacle(speed);
		obstacles[i]->setSpeedMultiplier(speedMultiplier);
		obstacles[i]->setDepth(i + 50);
	}
	gameMode = i;
	start = std::clock();
}

void app::gameOver()
{
	for (int i = 0; i < numberObstacles; i++)
	{
		obstacles[i] -> ~Obstacle();
	}
	scoreBoard->finalScore(duration, speedMultiplier);
	//finalScore = p1->getScore() * speedMultiplier;
	p1 -> ~player();
	gameMode = 3;
}