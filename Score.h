#include "agk.h"
#include <String>

class Score
{
private:
	int points;
	int highScores[10];
	int file;
	std::string scoreNames[10];
	int scoreDisplays[10];
	int background;
	int pointDisplay;
	int timeBonus;
	int speedMultiplier;
	int finalPoints;
	int UI;
	int gameOverScreen;
public:
	Score();
	~Score();
	void updateHighScores();
	void addPoints(int);
	void resetHighScores();
	void finalScore(int, int);
	void displayScores();
	void hideScores();
	int getPoints();
	void showScore();
	void hideFinalScore();
};