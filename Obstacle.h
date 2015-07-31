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
	int cloud;
	int spriteSize;
	bool notColliding;
public:
	Obstacle();
	Obstacle(int);
	~Obstacle();
	void update();
	int getSprite();
	void reset();
	void reset(int);
	void reset(int, int);
	int getType();
	int getXPos();
	void setSpeedMultiplier(int);
	void setDisabled();
	void setDepth(int);
	void cloudCover();
	bool getColliding();
	void setColliding(bool);
};