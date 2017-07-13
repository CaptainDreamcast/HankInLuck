#include "screen6.h"

#include <stdio.h>
#include <tari/input.h>
#include <tari/timer.h>

#include "hank.h"
#include "narrator.h"
#include "enemyhandler.h"
#include "collision.h"
#include "gamelogic.h"
#include "scrolling.h"
#include "boxgenerator.h"
#include "screen7.h"
#include "titlescreen.h"

static void levelOver(void* tCaller) {
	(void)tCaller;
	moveToNextScreen();
}

static void loadScreen6() {
	setHankName("GOOSE");
	setNarratorText("Hank flies away through the nuclear sky. Yet things are about to go awry.");
	setCurrentScreen(&Screen6);
	setNextScreen(&Screen7);

	setScrollingBGName("SKY");
	setupGameCollisions();
	instantiateActor(ScrollingBackgroundBP);
	instantiateActor(HankBP);
	instantiateActor(NarratorBP);
	instantiateActor(BoxGeneratorBP);
	setHankEvasionLevel();

	addTimerCB(30 * 60, levelOver, NULL);
}

Screen* getScreen6NextScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen Screen6 = {
	.mLoad = loadScreen6,
	.mGetNextScreen = getScreen6NextScreen,

};