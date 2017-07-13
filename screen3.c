#include "screen3.h"

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
#include "screen4.h"
#include "titlescreen.h"


static void levelOver(void* tCaller) {
	(void)tCaller;
	moveToNextScreen();
}

static void loadScreen3() {
	setHankName("HORSE");
	setNarratorText("Hank and horse, united in fear, galloped through the nuclear wasteland: \"Let's get away from here!\"");
	setCurrentScreen(&Screen3);
	setNextScreen(&Screen4);

	setScrollingBGName("SCROLLING");
	setupGameCollisions();
	instantiateActor(ScrollingBackgroundBP);
	instantiateActor(HankBP);
	instantiateActor(NarratorBP);
	instantiateActor(BoxGeneratorBP);
	setHankEvasionLevel();

	addTimerCB(30*60, levelOver, NULL);
}

Screen* getScreen3NextScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen Screen3 = {
	.mLoad = loadScreen3,
	.mGetNextScreen = getScreen3NextScreen,

};