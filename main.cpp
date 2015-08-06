// Includes
#include "main.h"
#include "Player.h"
#include "Obstacle.h"
#include "Background.h"
#include "Score.h"
#include "Menu.h"
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
Menu *menu;
int gameMode = 0;//what gamemode you're in
std::clock_t start;//start time of each day
double duration;//duration of the day
int dayLength = 60;//seconds in each day
int timeRemaining;
int lastTick = 0;
int speed = 9;
int speedMultiplier = 100;
int selection = 0;
int pauseScreen;
int volume = 100;
int music;
int musicVolume = 100;

void app::Begin(void)
{
	Aspect = ((float)agk::GetDeviceWidth() / agk::GetDeviceHeight());
	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetWindowTitle("Strawbirdie");
	agk::SetSyncRate(60,0);//max FPS?
	agk::SetScissor(0,0,0,0);//???
	agk::SetRandomSeed(agk::GetMilliseconds()); //seed the RNG based on system clock
	selection = 0;
	bg = new background();
	scoreBoard = new Score();
	menu = new Menu();
	pauseScreen = agk::CreateSprite(agk::LoadImage("assets/background/pause.png"));
	agk::SetSpriteDepth(pauseScreen, 1);
	agk::SetSpriteVisible(pauseScreen, 0);

	music = agk::LoadMusic("/assets/sounds/life_of_riley.mp3");
	agk::PlayMusic(music, 1);
}

void app::Loop (void)
{
	//agk::Print(agk::ScreenFPS());
	switch (gameMode)
	{
	case 0://main menu
		if (agk::GetRawKeyPressed(38) == 1)
			menu->changeSelection(-1);
		if (agk::GetRawKeyPressed(40) == 1)
			menu->changeSelection(1);
		if (agk::GetRawKeyPressed(32) == 1)
		{
			switch (menu->getSelection())
			{
			case 0://new game
				selection = 0;
				newGame(5);
				menu->hideMenu();
				break;
			case 1://scores
				gameMode = 6;
				menu->hideMenu();
				scoreBoard->displayScores();
				break;
			case 2://options
				gameMode = 4;
				selection = 0;
				menu->hideMenu();
				menu->showMenu(1);
				break;
			case 3://how to play
				menu->hideMenu();
				gameMode = 7;
				menu->showMenu(2);
				break;
			case 4://credits
				menu->hideMenu();
				gameMode = 7;
				menu->showMenu(3);
			}
		}
		break;
	case 3://game over
		if (agk::GetRawKeyPressed(13) == 1)
		{
			scoreBoard->hideFinalScore();
			gameMode = 0;
			menu->showMenu(0);
		}
		break;
	case 4://options
		if (agk::GetRawKeyPressed(38) == 1)
		{
			selection = menu->changeSelection(1);
		}
		if (agk::GetRawKeyPressed(40) == 1)
		{
			selection = menu->changeSelection(-1);
		}

		if (agk::GetRawKeyPressed(39) == 1)//right arrow
		{
			switch (selection)
			{
			case 1://sfxVolume
				volume += 10;
				if (volume > 100)
					volume = 100;
				menu->setSFXNumber(volume);
				break;
			case 2:
				musicVolume += 10;
				if (musicVolume > 100)
					musicVolume = 100;
				menu->setMusicNumber(musicVolume);
				agk::SetMusicSystemVolume(volume);
				break;
			case 3:
				speedMultiplier += 10;
				menu->setSpeedNumber(speedMultiplier);
				bg->setSpeed(speed, speedMultiplier);
				break;
			}
		}
		else if (agk::GetRawKeyPressed(37) == 1)//left arrow
		{
			switch (selection)
			{
			case 1://sfxVolume
				volume -= 10;
				if (volume < 0)
					volume = 0;
				menu->setSFXNumber(volume);
				break;
			case 2:
				musicVolume -= 10;
				if (musicVolume < 0)
					musicVolume = 0;
				menu->setMusicNumber(musicVolume);
				agk::SetMusicSystemVolume(musicVolume);
				break;
			case 3:
				speedMultiplier -= 10;
				if (speedMultiplier < 0)
					speedMultiplier = 0;
				menu->setSpeedNumber(speedMultiplier);
				bg->setSpeed(speed, speedMultiplier);
				break;
			}
		}
		else if (agk::GetRawKeyPressed(32) == 1)
		{
			switch (selection)
			{
			case 0:
				menu->hideMenu();
				gameMode = 0;
				menu->showMenu(0);
				break;
			}
		}
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
			if ( (std::clock() - start) / (double)CLOCKS_PER_SEC > .5)//if it's been a second since the last second
			{
				duration += 0.5;
				start = std::clock();
				p1->loseSize(1);
				if (p1->getHealth() < 1)
					gameOver();
			}
			if (agk::GetRawKeyPressed(27) == 1)//escape pressed
			{
				selection = 1;
				agk::SetSpriteVisible(pauseScreen, 1);
			}
		}
		else
		{
			if (agk::GetRawKeyPressed(27) == 1)//escape pressed
			{
				selection = 0;
				start = std::clock();
				agk::SetSpriteVisible(pauseScreen, 0);
			}
			if (agk::GetRawKeyPressed(46) == 1)//delete pressed
			{
				selection = 0;
				agk::SetSpriteVisible(pauseScreen, 0);
				gameOver();
			}
		}
			break;
	case 6://high scores
		if (agk::GetRawKeyPressed(32) == 1)//space pressed
		{
			gameMode = 0;
			scoreBoard->hideScores();
			menu->showMenu(0);
		}
		if (agk::GetRawKeyPressed(46) == 1)//delete pressed
		{
			scoreBoard->resetHighScores();
			scoreBoard->displayScores();
		}
		break;
	case 7://how to play
		if (agk::GetRawKeyPressed(32) == 1)
		{
			gameMode = 0;
			menu->showMenu(0);
			selection = menu->changeSelection(0);
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
					p1->gainSize(8);
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
	p1 = new player(volume);

	for (int i = 0; i < numberObstacles; i++)
	{
		obstacles[i] = new Obstacle(speed);
		obstacles[i]->setSpeedMultiplier(speedMultiplier);
		obstacles[i]->setDepth(i + 50);
	}
	gameMode = i;
	start = std::clock();
	duration = 0;
	scoreBoard->showScore();
	p1->setHealthVisible(1);
}

void app::gameOver()
{
	for (int i = 0; i < numberObstacles; i++)
	{
		obstacles[i] -> ~Obstacle();
	}
	scoreBoard->finalScore(duration, speedMultiplier);
	//finalScore = p1->getScore() * speedMultiplier;
	p1->setHealthVisible(0);
	p1 -> ~player();
	gameMode = 3;
}