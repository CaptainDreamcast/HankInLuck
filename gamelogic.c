#include "gamelogic.h"

static struct {
	Screen* tCurrentScreen;
	Screen* tNextScreen;

} gData;

void setCurrentScreen(Screen * tScreen)
{
	gData.tCurrentScreen = tScreen;
}

void setNextScreen(Screen * tScreen)
{
	gData.tNextScreen = tScreen;
}

void moveToNextScreen()
{
	setNewScreen(gData.tNextScreen);
}

void moveToCurrentScreen()
{
	setNewScreen(gData.tCurrentScreen);
}
