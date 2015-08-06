#include "agk.h"

class background
{
private:
	int backGround1;
	int backGround1x;
	int backGround2;
	int backGround2x;
	int ground1;
	int ground1x;
	int ground2;
	int ground2x;
	int speed;
public:
	background();
	~background();
	void setSpeed(int, int);
	void update();
};