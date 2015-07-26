#include "agk.h"
#include <ctime>

class player
{
private:
	std::clock_t timer;//used for i-frames
	int xPos;
	int yPos; //vertical position
	int speed; //vertical movement speed
	int sprite;
	int score;
	//form
	int health;
	int size;
	int invincibleTime;
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
	void setInvincible(int);
	int getInvincibleTime();
};