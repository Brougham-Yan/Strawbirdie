#include "agk.h"
#include <math.h>

class Obstacle
{
private:
	int type;
	int sprite;
	int speed;
	int speedMultiplier;
	int yPos;
	int xPos;
	int strawberry;
	int enemy;
	int popsicle;
	int spriteSize;
public:
	Obstacle();
	~Obstacle();
	void update();
	int getSprite();
	void reset();
	void reset(int);
	int getType();
	int getXPos();
	void setSpeedMultiplier(int);
	void setDisabled();
	void setDepth(int);
};