// Includes
#include "main.h"
#include "Player.h"
#include "Obstacle.h"
#include <ctime>
// Namespace
using namespace AGK;

app App;
const int numberObstacles = 30; //number of obstacles allowed on screen at once; 
float Aspect = 0.0;
player *p1;
Obstacle *obstacles[numberObstacles];
bool endGame = false;//tells if you're at game over
int gameMode = 0;//what gamemode you're in
std::clock_t start;//start time of each day
double duration;//duration of the day
int dayLength = 60;//seconds in each day
int timeRemaining;

void app::Begin(void)
{
	Aspect = ((float)agk::GetDeviceWidth() / agk::GetDeviceHeight());
	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);//max FPS?
	agk::SetScissor(0,0,0,0);
	agk::SetRandomSeed(agk::GetMilliseconds()); //seed the RNG based on system clock
}

void app::Loop (void)
{
	agk::Print(agk::ScreenFPS());
	switch (gameMode)
	{
	case 0://main menu
		agk::Print("Main Menu");
		agk::Print("Press space to start");
		if (agk::GetRawKeyState(40) == 1)
			newGame();
		break;


	case 1://in game
		if (!endGame)
		{
			p1->update();
			for (int i = 0; i < numberObstacles; i++)
			{
				obstacles[i]->update();
			}
			CheckCollisions();
		}
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		timeRemaining = dayLength - (int)duration;
		if (timeRemaining < 0)
		{
			gameMode = 2;
			//some sort of function here
		}
		agk::Print(timeRemaining);
		agk::Print(p1->getScore());
		if (p1->getHealth() > 0)
			agk::Print(p1->getHealth());
		else
			gameMode = 3;//game over
		break;
	case 2:
		agk::Print("Day Over");
		break;
	case 3:
		agk::Print("Game Over");
		break;
	}

	agk::Sync();
}


void app::End (void)
{

}

void app::CheckCollisions()
{
	for (int i = 0; i < numberObstacles; i++)
	{
		if (obstacles[i]->getXPos() < 250)
		{
			if (agk::GetSpriteCollision(p1->getSprite(), obstacles[i]->getSprite()) == true)
			{
				if (obstacles[i]->getType() == 0)
				{
					p1->addPoints(1);
				}
				else if (obstacles[i]->getType() == 1){
					p1->loseHealth(1);
					if (p1->getHealth() < 1)
					{
						gameOver();
						return;
					}
				}
				obstacles[i]->reset();
			}
		}
	}
}

void app::newGame()
{
	p1 = new player();

	for (int i = 0; i < numberObstacles; i++)
	{
		obstacles[i] = new Obstacle();
	}
	gameMode = 1;
	start = std::clock();
}

void app::gameOver()
{
	for (int i = 0; i < numberObstacles; i++)
	{
		delete obstacles[i];
	}
	p1->updateSprite(0);
	agk::Print("Game Over");
	endGame = true;
}