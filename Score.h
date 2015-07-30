#include "agk.h"
#include <String>

class Score
{
private:
	int points;
	int highScores[10];
	int file;
	std::string scoreNames[10];
public:
	Score();
	~Score();
	void updateHighScores();
	void addPoints(int);
	void resetHighScores();
	void finalScore(int, int);
	void displayScores();
	int getPoints();
};