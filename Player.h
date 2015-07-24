#include "agk.h"

class player
{
private:
	int xPos;
	int yPos; //vertical position
	int speed; //vertical movement speed
	int sprite;
	int score;
	//form
	int health;
	int size;
	//food
public:
	player();
	~player();
	void update();
	int getSprite();
	void addPoints(int);
	int getScore();
	void loseHealth(int);
	void gainHealth(int);
	int getHealth();
	void updateSprite(int);
	void loseSize(int);
	void gainSize(int);
};