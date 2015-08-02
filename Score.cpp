#include "Score.h"
using namespace AGK;

Score::Score()
{
	points = 0;
	if (agk::GetFileExists("scores.dat") != 1)
		resetHighScores();
	else{
		file = agk::OpenToRead("scores.dat");
		for (int i = 0; i < 10; i++)
		{
			highScores[i] = agk::ReadInteger(file);
			scoreNames[i] = agk::ReadString(file);
		}
		agk::CloseFile(file);
	}
	for (int i = 0; i < 10; i++)
		scoreDisplays[i] = agk::CreateText("");
	background = agk::CreateSprite(0);
	agk::SetSpritePosition(background, 262, 100);
	agk::SetSpriteSize(background, 500, 500);
	agk::SetSpriteColor(background, 75, 150, 250, 255);
	agk::SetSpriteVisible(background, 0);
	pointDisplay = agk::CreateText("0");
	agk::SetTextSize(pointDisplay, 40);
	agk::SetTextPosition(pointDisplay, 25, 725);
	agk::SetTextVisible(pointDisplay, 0);

	timeBonus = agk::CreateText("0");
	agk::SetTextSize(timeBonus, 40);
	agk::SetTextVisible(timeBonus, 0);

	speedMultiplier = agk::CreateText("0");
	agk::SetTextSize(speedMultiplier, 40);
	agk::SetTextVisible(speedMultiplier, 0);

	finalPoints = agk::CreateText("0");
	agk::SetTextSize(finalPoints, 40);
	agk::SetTextVisible(finalPoints, 0);

	agk::SetTextPosition(pointDisplay, 300, 225);
	agk::SetTextPosition(speedMultiplier, 300, 275);
	agk::SetTextPosition(timeBonus, 300, 325);
	agk::SetTextPosition(finalPoints, 300, 375);
	agk::SetTextColor(finalPoints, 200, 255, 200, 255);
}

void Score::resetHighScores()
{
	file = agk::OpenToWrite("scores.dat");
	for (int i = 0; i < 10; i++)
	{
		agk::WriteInteger(file, 0);
		agk::WriteString(file, "Player");
	}
	agk::CloseFile(file);
}

void Score::addPoints(int i)
{
	points += i;
	std::string s = std::to_string(points);
	agk::SetTextString(pointDisplay, s.c_str());
}

void Score::finalScore(int time, int multiplier)
{
	agk::SetSpriteVisible(background, 1);
	agk::SetTextVisible(pointDisplay, 1);
	agk::SetTextVisible(speedMultiplier, 1);
	agk::SetTextVisible(timeBonus, 1);
	agk::SetTextVisible(finalPoints, 1);

	agk::SetTextPosition(pointDisplay, 300, 225);
	agk::SetTextPosition(speedMultiplier, 300, 275);
	agk::SetTextPosition(timeBonus, 300, 325);
	agk::SetTextPosition(finalPoints, 300, 375);
	agk::SetTextColor(finalPoints, 200, 255, 200, 255);

	std::string s = std::to_string(points);
	agk::SetTextString(pointDisplay, s.c_str());

	s = std::to_string(time);
	agk::SetTextString(timeBonus, s.c_str());

	s = std::to_string(multiplier);
	agk::SetTextString(speedMultiplier, s.c_str());

	points = (points * multiplier);
	points += (time * 5);

	s = std::to_string(points);
	agk::SetTextString(finalPoints, s.c_str());

	updateHighScores();
	points = 0;
}

void Score::updateHighScores()
{
	if (points > highScores[9])
	{
		highScores[9] = points;
		scoreNames[9] = "Player";
		bool done = false;
		int i = 9;
		while (!done)
		{
			if (highScores[i] > highScores[i - 1])
			{
				int holder = highScores[i - 1];
				highScores[i - 1] = highScores[i];
				highScores[i] = holder;
			}
			else
				done = true;
			if (i > 1)
				i--;
			else
				done = true;
		}

		file = agk::OpenToWrite("scores.dat");
		for (int i = 0; i < 10; i++)
		{
			agk::WriteInteger(file, highScores[i]);
			agk::WriteString(file, "Player");
		}
		agk::CloseFile(file);

	}
}

void Score::displayScores()
{
	for (int i = 0; i < 9; i++)
	{
		std::string s = std::to_string(highScores[i]);
		agk::SetTextString(scoreDisplays[i], s.c_str());
		agk::SetTextPosition(scoreDisplays[i], 450, (i * 50 + 125));
		agk::SetTextSize(scoreDisplays[i], 30);
		agk::SetTextVisible(scoreDisplays[i], 1);
	}
	agk::SetSpriteVisible(background, 1);
}

void Score::hideScores()
{
	for (int i = 0; i < 9; i++)
		agk::SetTextVisible(scoreDisplays[i], 0);
	agk::SetSpriteVisible(background, 0);
}

int Score::getPoints()
{
	return points;
}

void Score::showScore()
{
	agk::SetTextPosition(pointDisplay, 25, 725);
	std::string s = std::to_string(points);
	agk::SetTextString(pointDisplay, s.c_str());
	agk::SetTextVisible(pointDisplay, 1);
}

void Score::hideFinalScore()
{
	agk::SetSpriteVisible(background, 0);
	agk::SetTextVisible(pointDisplay, 0);
	agk::SetTextVisible(speedMultiplier, 0);
	agk::SetTextVisible(timeBonus, 0);
	agk::SetTextVisible(finalPoints, 0);
}