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
public:
	Menu();
	~Menu();
	void hideMenu();
	void showMenu(int);
	void changeSelection(int);
	int getSelection();
	void setSpeedNumber(int);
};