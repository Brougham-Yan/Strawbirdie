#include "agk.h"
#include <ctime>
#include <string>

class player
{
private:
	std::clock_t timer;//used for i-frames
	int xPos;
	int yPos; //vertical position
	int speed; //vertical movement speed
	int playerSprite;
	int score;
	int health;
	int healthDisplay;
	int size;
	int invincibleTime;
	float velocity;
	int hitSound;
	int healthSound;
	int pickupSound;
	int volume;

public:
	player(int);
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
	void setHealthVisible(int);
};