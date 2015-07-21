// Includes
#include "main.h"
#include "Player.h"
#include "Obstacle.h"
// Namespace
using namespace AGK;

app App;
const int numberObstacles = 30;
float Aspect = 0.0;
player *p1;
Obstacle *obstacles[numberObstacles];
bool endGame = false;

void app::Begin(void)
{
	Aspect = ((float)agk::GetDeviceWidth() / agk::GetDeviceHeight());
	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);//max FPS?
	agk::SetScissor(0,0,0,0);

	p1 = new player();

	for (int i = 0; i < numberObstacles; i++)
	{
		obstacles[i] = new Obstacle();
	}

	agk::SetRandomSeed(agk::GetMilliseconds()); //seed the RNG based on system clock
}

void app::Loop (void)
{
	if (!endGame)
	{
		p1->update();
		for (int i = 0; i < numberObstacles; i++)
		{
			obstacles[i]->update();
		}
		CheckCollisions();
	}
	agk::Print( agk::ScreenFPS() );
	agk::Print(p1->getScore());
	int i = p1->getHealth();
	if (i > 0)
		agk::Print(p1->getHealth());
	else
		agk::Print("Game Over");
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