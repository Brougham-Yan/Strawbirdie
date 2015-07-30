#include "Background.h"

background::background()
{
	backGround1 = agk::CreateSprite(agk::LoadImage("/assets/background/layer-1.png"));
	backGround1x = 0;
	backGround2 = agk::CreateSprite(agk::LoadImage("/assets/background/layer-1.png"));
	backGround2x = 1536;
	ground1 = agk::CreateSprite(agk::LoadImage("/assets/background/layer-2.png"));
	ground1x = 0;
	ground2 = agk::CreateSprite(agk::LoadImage("/assets/background/layer-2.png"));
	ground2x = 1536;
	speed = 10;

	agk::SetSpriteColor(backGround1, 255, 255, 255, 255);

	agk::SetSpriteSize(backGround1, -1, 768);
	agk::SetSpriteSize(backGround2, -1, 768);
	agk::SetSpriteDepth(backGround1, 150);
	agk::SetSpriteDepth(backGround2, 151);

	agk::SetSpriteSize(ground1, -1, 768);
	agk::SetSpriteSize(ground2, -1, 768);
	agk::SetSpriteDepth(ground1, 100);
	agk::SetSpriteDepth(ground2, 101);

	agk::SetSpritePosition(backGround1, backGround1x, 0);
	agk::SetSpritePosition(backGround2, backGround2x, 0);
	agk::SetSpritePosition(ground1, ground1x, 0);
	agk::SetSpritePosition(ground2, ground2x, 0);
}

void background::setSpeed(int i)
{
	speed = i;
}

void background::update()
{
	backGround1x -= (speed - 5);
	backGround2x -= (speed - 5);
	ground1x -= speed;
	ground2x -= speed;

	if (backGround1x < -1536)
		backGround1x += 3072;
	if (backGround2x < -1536)
		backGround2x += 3072;
	if (ground1x < -1536)
		ground1x += 3072;
	if (ground2x < -1536)
		ground2x += 3072;

	agk::SetSpritePosition(backGround1, backGround1x, 0);
	agk::SetSpritePosition(backGround2, backGround2x, 0);
	agk::SetSpritePosition(ground1, ground1x, 0);
	agk::SetSpritePosition(ground2, ground2x, 0);
}