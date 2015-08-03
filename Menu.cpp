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
	agk::SetTextSize(startGame, 50);
	agk::SetTextSize(options, 50);
	agk::SetTextSize(highScores, 50);

	agk::SetTextPosition(startGame, 280, 150);
	agk::SetTextPosition(options, 280, 350);
	agk::SetTextPosition(highScores, 280, 250);

	agk::SetTextColor(startGame, 0, 255, 0, 255);

	back = agk::CreateText("Back");
	speedMultiplier = agk::CreateText("Speed Multiplier:");
	speedNumber = agk::CreateText("100");
	agk::SetTextSize(back, 50);
	agk::SetTextSize(speedMultiplier, 40);
	agk::SetTextSize(speedNumber, 50);
	agk::SetTextPosition(back, 280, 400);
	agk::SetTextPosition(speedMultiplier, 280, 150); 
	agk::SetTextPosition(speedNumber, 400, 200);
	agk::SetTextVisible(back, 0);
	agk::SetTextVisible(speedMultiplier, 0);
	agk::SetTextVisible(speedNumber, 0);

	tutorial = agk::CreateSprite(agk::LoadImage("/assets/background/howtoplay.png"));
	agk::SetSpriteDepth(tutorial, 3);
	agk::SetSpriteVisible(tutorial, 0);

	howToPlay = agk::CreateText("How to Play");
	agk::SetTextSize(howToPlay, 50);
	agk::SetTextPosition(howToPlay, 280, 250);
	agk::SetTextVisible(howToPlay, 0);
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
		break;
	case 1:
		agk::SetSpriteVisible(menuBG, 1);
		agk::SetTextColor(back, 0, 255, 0, 255);
		agk::SetTextVisible(back, 1);
		agk::SetTextVisible(speedMultiplier, 1);
		agk::SetTextVisible(speedNumber, 1);
		agk::SetTextVisible(howToPlay, 1);
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
			selection = 2;
		else if (selection > 2)
			selection = 0;
		switch (selection)
		{
		case 0:
			agk::SetTextColor(startGame, 0, 255, 0, 255);
			agk::SetTextColor(options, 255, 255, 255, 255);
			agk::SetTextColor(highScores, 255, 255, 255, 255);
			break;
		case 1:
			agk::SetTextColor(startGame, 255, 255, 255, 255);
			agk::SetTextColor(options, 0, 255, 0, 255);
			agk::SetTextColor(highScores, 255, 255, 255, 255);
			break;
		case 2:
			agk::SetTextColor(startGame, 255, 255, 255, 255);
			agk::SetTextColor(options, 255, 255, 255, 255);
			agk::SetTextColor(highScores, 0, 255, 0, 255);
			break;
		}
		break;
	case 1:
		if (selection < 0)
			selection = 2;
		else if (selection > 2)
			selection = 0;
		agk::SetTextColor(speedMultiplier, 255, 255, 255, 255);
		agk::SetTextColor(speedNumber, 255, 255, 255, 255);
		agk::SetTextColor(back, 255, 255, 255, 255);
		agk::SetTextColor(howToPlay, 255, 255, 255, 255);

		switch (selection)
		{
		case 0:
			agk::SetTextColor(back, 0, 255, 0, 255);
			break;
		case 1:
			agk::SetTextColor(howToPlay, 0, 255, 0, 255);
			break;
		case 2:
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