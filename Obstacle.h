#include "agk.h"

class Obstacle
{
private:
	int type;
	int sprite;
	int speed;
	int speedMultiplier;
	int yPos;
	int xPos;
public:
	Obstacle();
	~Obstacle();
	void update();
	int getSprite();
	void reset();
	int getType();
	int getXPos();
	void setSpeedMultiplier(int);
};