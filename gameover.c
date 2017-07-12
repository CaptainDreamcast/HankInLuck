#include "gameover.h"

#include <tari/animation.h>
#include <tari/optionhandler.h>
#include <tari/input.h>

#include "gamelogic.h"
#include "titlescreen.h"

static struct {
	TextureData mTexture;
	int mAnimation;
} gData;

static void selectContinue(void* tCaller) {
	(void)tCaller;
	moveToCurrentScreen();
}

static void selectTitle(void* tCaller) {
	setNewScreen(&TitleScreen);
}

static void loadGameOverScreen() {
	instantiateActor(getOptionHandlerBlueprint());
	setOptionButtonA();
	setOptionButtonStart();
	setOptionTextSize(20);
	setOptionTextBreakSize(-5);

	addOption(makePosition(150, 300, 2), "Continue", selectContinue, NULL);
	addOption(makePosition(150, 330, 2), "Return to Title", selectTitle, NULL);

	gData.mTexture = loadTexture("assets/sprites/GAMEOVER.pkg");
	playOneFrameAnimationLoop(makePosition(0, 0, 1), &gData.mTexture);
}

static Screen* getNextGameOverScreenScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}


Screen GameOverScreen = {
	.mLoad = loadGameOverScreen,
	.mGetNextScreen = getNextGameOverScreenScreen,
};