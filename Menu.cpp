#include "Menu.h"

Menu::Menu()
{
	selection = 0;
	menuType = 0;
	menuBG = agk::CreateSprite(agk::LoadImage("/assets/background/menus.png"));;
	//agk::SetSpriteColor(menuBG, 75, 150, 250, 255);
	//agk::SetSpritePosition(menuBG, 262, 100);
	//agk::SetSpriteSize(menuBG, 500, 400);


	startGame = agk::CreateText("Start Game");
	options = agk::CreateText("Options");
	highScores = agk::CreateText("High Scores");
	howToPlay = agk::CreateText("How to Play");

	agk::SetTextSize(startGame, 50);
	agk::SetTextSize(options, 50);
	agk::SetTextSize(highScores, 50);
	agk::SetTextSize(howToPlay, 50);

	agk::SetTextPosition(startGame, 280, 150);
	agk::SetTextPosition(highScores, 280, 250);
	agk::SetTextPosition(options, 280, 350);
	agk::SetTextPosition(howToPlay, 280, 450);

	agk::SetTextColor(startGame, 0, 255, 0, 255);

	back = agk::CreateText("Back");
	speedMultiplier = agk::CreateText("Speed Multiplier:");
	speedNumber = agk::CreateText("100");
	musicVolume = agk::CreateText("Music Volume:");
	musicVolumeNumber = agk::CreateText("100");
	sfxVolume = agk::CreateText("SFX Volume:");
	sfxVolumeNumber = agk::CreateText("100");
	tutorial = agk::CreateSprite(agk::LoadImage("/assets/background/howtoplay.png"));

	agk::SetTextSize(back, 50);//options formatting
	agk::SetTextSize(speedMultiplier, 40);
	agk::SetTextSize(speedNumber, 50);
	agk::SetTextSize(musicVolume, 40);
	agk::SetTextSize(musicVolumeNumber, 50);
	agk::SetTextSize(sfxVolume, 40);
	agk::SetTextSize(sfxVolumeNumber, 50);

	agk::SetTextPosition(speedMultiplier, 280, 150); 
	agk::SetTextPosition(speedNumber, 450, 200);
	agk::SetTextPosition(musicVolume, 280, 250);
	agk::SetTextPosition(musicVolumeNumber, 450, 300);
	agk::SetTextPosition(sfxVolume, 280, 350);
	agk::SetTextPosition(sfxVolumeNumber, 450, 400);

	agk::SetTextPosition(back, 280, 600);


	agk::SetSpriteDepth(tutorial, 3);
	agk::SetSpriteVisible(tutorial, 0);
	agk::SetTextVisible(back, 0);
	agk::SetTextVisible(speedMultiplier, 0);
	agk::SetTextVisible(speedNumber, 0);
	agk::SetTextVisible(musicVolume, 0);
	agk::SetTextVisible(musicVolumeNumber, 0);
	agk::SetTextVisible(sfxVolume, 0);
	agk::SetTextVisible(sfxVolumeNumber, 0);
}

void Menu::hideMenu()
{
	agk::SetSpriteVisible(menuBG, 0);
	agk::SetTextColor(startGame, 255, 255, 255, 255);
	agk::SetTextVisible(startGame, 0);
	agk::SetTextColor(options, 255, 255, 255, 255);
	agk::SetTextVisible(options, 0);
	agk::SetTextColor(highScores, 255, 255, 255, 255);
	agk::SetTextVisible(highScores, 0);
	agk::SetTextColor(back, 255, 255, 255, 255);
	agk::SetTextVisible(back, 0);
	agk::SetTextColor(speedMultiplier, 255, 255, 255, 255);
	agk::SetTextVisible(speedMultiplier, 0);
	agk::SetTextColor(speedNumber, 255, 255, 255, 255);
	agk::SetTextVisible(speedNumber, 0);
	agk::SetSpriteVisible(tutorial, 0);
	agk::SetTextVisible(howToPlay, 0);
	agk::SetTextColor(howToPlay, 255, 255, 255, 255);
	agk::SetTextColor(musicVolume, 255, 255, 255, 255);
	agk::SetTextVisible(musicVolume, 0);
	agk::SetTextColor(musicVolumeNumber, 255, 255, 255, 255);
	agk::SetTextVisible(musicVolumeNumber, 0);
	agk::SetTextColor(sfxVolume, 255, 255, 255, 255);
	agk::SetTextVisible(sfxVolume, 0);
	agk::SetTextColor(sfxVolumeNumber, 255, 255, 255, 255);
	agk::SetTextVisible(sfxVolumeNumber, 0);
}

void Menu::showMenu(int i)
{
	hideMenu();
	menuType = i;
	selection = 0;
	switch (menuType)
	{
	case 0:
		agk::SetSpriteVisible(menuBG, 1);
		agk::SetTextColor(startGame, 0, 255, 0, 255);
		agk::SetTextVisible(startGame, 1);
		agk::SetTextVisible(options, 1);
		agk::SetTextVisible(highScores, 1);
		agk::SetTextVisible(howToPlay, 1);
		break;
	case 1:
		agk::SetSpriteVisible(menuBG, 1);
		agk::SetTextColor(back, 0, 255, 0, 255);
		agk::SetTextVisible(back, 1);
		agk::SetTextVisible(speedMultiplier, 1);
		agk::SetTextVisible(speedNumber, 1);
		agk::SetTextVisible(musicVolume, 1);
		agk::SetTextVisible(musicVolumeNumber, 1);
		agk::SetTextVisible(sfxVolume, 1);
		agk::SetTextVisible(sfxVolumeNumber, 1);
		break;
	case 2:
		agk::SetSpriteVisible(tutorial, 1);
		break;
	}
}

int Menu::changeSelection(int i)
{
	selection += i;
	switch (menuType)
	{
	case 0:
		if (selection < 0)
			selection = 3;
		else if (selection > 3)
			selection = 0;
		agk::SetTextColor(startGame, 255, 255, 255, 255);
		agk::SetTextColor(options, 255, 255, 255, 255);
		agk::SetTextColor(highScores, 255, 255, 255, 255);
		agk::SetTextColor(howToPlay, 255, 255, 255, 255);

		switch (selection)
		{
		case 0:
			agk::SetTextColor(startGame, 0, 255, 0, 255);
			break;
		case 1:
			agk::SetTextColor(highScores, 0, 255, 0, 255);
			break;
		case 2:
			agk::SetTextColor(options, 0, 255, 0, 255);
			break;
		case 3:
			agk::SetTextColor(howToPlay, 0, 255, 0, 255);
			break;
		}
		break;
	case 1:
		if (selection < 0)
			selection = 3;
		else if (selection > 3)
			selection = 0;
		agk::SetTextColor(speedMultiplier, 255, 255, 255, 255);
		agk::SetTextColor(speedNumber, 255, 255, 255, 255);
		agk::SetTextColor(back, 255, 255, 255, 255);
		agk::SetTextColor(musicVolume, 255, 255, 255, 255);
		agk::SetTextColor(musicVolumeNumber, 255, 255, 255, 255);
		agk::SetTextColor(sfxVolume, 255, 255, 255, 255);
		agk::SetTextColor(sfxVolumeNumber, 255, 255, 255, 255);

		switch (selection)
		{
		case 0:
			agk::SetTextColor(back, 0, 255, 0, 255);
			break;
		case 1:
			agk::SetTextColor(sfxVolume, 0, 255, 0, 255);
			agk::SetTextColor(sfxVolumeNumber, 0, 255, 0, 255);
			break;
		case 2:
			agk::SetTextColor(musicVolume, 0, 255, 0, 255);
			agk::SetTextColor(musicVolumeNumber, 0, 255, 0, 255);
			break;
		case 3:
			agk::SetTextColor(speedMultiplier, 0, 255, 0, 255);
			agk::SetTextColor(speedNumber, 0, 255, 0, 255);
			break;
		}
		break;
	}
	return selection;
}

int Menu::getSelection()
{
	return selection;
}

void Menu::setSpeedNumber(int i)
{
	std::string s = std::to_string(i);
	agk::SetTextString(speedNumber, s.c_str());
}

void Menu::setMusicNumber(int i)
{
	std::string s = std::to_string(i);
	agk::SetTextString(musicVolumeNumber, s.c_str());
}

void Menu::setSFXNumber(int i)
{
	std::string s = std::to_string(i);
	agk::SetTextString(sfxVolumeNumber, s.c_str());
}