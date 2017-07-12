#include "titlescreen.h"

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

static struct {
	TextureData mBGTexture;
	int mBG;

} gData;

static void loadTitleScreen() {
	setCurrentScreen(&TitleScreen);
	setNextScreen(&Screen1);

	setNarratorText("This tale happened a long long time ago in a country far far away. Press Start to let the story play.");
	instantiateActor(NarratorBP);

	gData.mBGTexture = loadTexture("assets/sprites/TITLE.pkg");
	gData.mBG = playOneFrameAnimationLoop(makePosition(0, 0, 1), &gData.mBGTexture);
}

Screen* getNextTitleScreenScreen() {
	
	if (hasPressedAbortFlank()) {
		abortScreenHandling();
	}

	if (hasPressedStartFlank()) {
		return &Screen1;
	}

	return NULL;
}

Screen TitleScreen = {
	.mLoad = loadTitleScreen,
	.mGetNextScreen = getNextTitleScreenScreen,
};