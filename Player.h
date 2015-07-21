#include "agk.h"

class player
{
private:
	int yPos; //vertical position
	int speed; //vertical movement speed
	int sprite;
	int score;
	//form
	int health;
	//food
public:
	player();
	~player();
	void update();
	int getSprite();
	void addPoints(int);
	int getScore();
	void loseHealth(int);
	int getHealth();
	void updateSprite(int);
};