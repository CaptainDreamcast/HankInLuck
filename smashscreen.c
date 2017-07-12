#include "smashscreen.h"

#include <stdio.h>

#include <tari/input.h>
#include <tari/animation.h>

#include "bg.h"
#include "hank.h"
#include "narrator.h"
#include "enemyhandler.h"
#include "collision.h"
#include "gamelogic.h"
#include "screen1.h"
#include "titlescreen.h"

static struct {
	TextureData mBGTexture;
	int mBG;

	Screen* mNextScreen;
	char mNarratorText[1024];
} gData;

static void loadSmashScreen() {
	setCurrentScreen(&SmashScreen);
	setNextScreen(gData.mNextScreen);

	setNarratorText(gData.mNarratorText);
	instantiateActor(NarratorBP);

	gData.mBGTexture = loadTexture("assets/sprites/SMASH.pkg");
	gData.mBG = playOneFrameAnimationLoop(makePosition(0, 0, 1), &gData.mBGTexture);
}

Screen* getNextSmashScreenScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	if (hasPressedStartFlank()) {
		return gData.mNextScreen;
	}

	return NULL;
}

Screen SmashScreen = {
	.mLoad = loadSmashScreen,
	.mGetNextScreen = getNextSmashScreenScreen,
};

void setSmashScreenNarrationAndAfterScreen(char * tText, Screen * tScreenAfter)
{
	strcpy(gData.mNarratorText, tText);
	gData.mNextScreen = tScreenAfter;
}
