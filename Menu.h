#include "agk.h"
#include <string>

class Menu
{
private:
	int menuBG;
	int startGame;
	int options;
	int highScores;
	int selection;
	int menuType;
	int back;

	int speedMultiplier;
	int speedNumber;
	int tutorial;
	int howToPlay;
	int musicVolume;
	int musicVolumeNumber;
	int sfxVolume;
	int sfxVolumeNumber;

public:
	Menu();
	~Menu();
	void hideMenu();
	void showMenu(int);
	int changeSelection(int);
	int getSelection();
	void setSpeedNumber(int);
	void setMusicNumber(int);
	void setSFXNumber(int);

};