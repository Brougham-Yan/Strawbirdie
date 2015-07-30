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
}

void Score::finalScore(int time, int multiplier)
{
	points = (points * multiplier);
	points += (time * 5);
	updateHighScores();
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
	agk::Print("High Scores:");
	for (int i = 0; i < 9; i++)
	{
		agk::Print(highScores[i]);
	}
	agk::Print("Press space to return");
}

int Score::getPoints()
{
	return points;
}