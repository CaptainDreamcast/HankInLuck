#include "congratsscreen.h"

#include <stdio.h>

#include <tari/input.h>
#include <tari/animation.h>
#include <tari/timer.h>

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
	int mNarrationAmount;
	int mCurrent;
	int mTimer;
} gData;

static char gNarrations[6][1024] = {
	"At last, you've reached the journey's end, for this I want to thank you, friend.",
	"Hank's trading mission now fulfilled, with only 6 bystanders killed.",
	"They weren't killed but just knocked out, so please don't call dear Hank a fraud.",
	"The story's moral as it stands, is never venture into foreign lands,",
	"without a pirate stone and duck, or else rely on your dumb luck.",
	"Yeah that rhyme was horrible, okay?. Thanks for playing anyway.",
};

static void setNextNarration(void* tCaller) {
	(void)tCaller;
	if (gData.mCurrent == gData.mNarrationAmount) {
		setNewScreen(&TitleScreen);
	}

	setNarratorText(gNarrations[gData.mCurrent++]);
	gData.mTimer = addTimerCB(800, setNextNarration, NULL);
}


static void loadCongratsScreen() {
	setCurrentScreen(&CongratsScreen);
	setNextScreen(&TitleScreen);

	gData.mNarrationAmount = 6;
	gData.mCurrent = 0;
	setNextNarration(NULL);
	instantiateActor(NarratorBP);

	gData.mBGTexture = loadTexture("assets/sprites/CONGRATS.pkg");
	gData.mBG = playOneFrameAnimationLoop(makePosition(0, 0, 1), &gData.mBGTexture);
}

Screen* getNextCongratsScreenScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	if (hasPressedStartFlank()) {
		if (gData.mTimer != -1) {
			removeTimer(gData.mTimer);
			gData.mTimer = -1;
		}
		if (gData.mCurrent >= gData.mNarrationAmount) {
			return &TitleScreen;
		}
		setNextNarration(NULL);
	}
	else if (hasPressedAFlank()) {
		if (gData.mTimer != -1) {
			removeTimer(gData.mTimer);
			gData.mTimer = -1;
		}
		
		if (gData.mCurrent >= gData.mNarrationAmount) {
			return &TitleScreen;
		}
		setNextNarration(NULL);

	}

	

	return NULL;
}

Screen CongratsScreen = {
	.mLoad = loadCongratsScreen,
	.mGetNextScreen = getNextCongratsScreenScreen,
};