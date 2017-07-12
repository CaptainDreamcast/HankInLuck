#include "screen8.h"

#include <stdio.h>
#include <tari/input.h>

#include "hank.h"
#include "narrator.h"
#include "enemyhandler.h"
#include "collision.h"
#include "gamelogic.h"
#include "bg.h"
#include "horseguy.h"
#include "titlescreen.h"
#include "finalboss.h"
#include "congratsscreen.h"


static void loadScreen8() {
	setHankName("STONE");
	setNarratorText("Stone in hand and fiends in reach, finally Hank is unleashed.");
	setCurrentScreen(&Screen8);
	setNextScreen(&CongratsScreen);

	setupGameCollisions();
	instantiateActor(BackgroundBP);
	instantiateActor(HankBP);
	instantiateActor(NarratorBP);

	loadFinalBosses();
	addFinalBoss(makePosition(400, 130, 2));
	addFinalBoss(makePosition(350, 200, 2));
	addFinalBoss(makePosition(480, 150, 2));
}

static void updateScreen8() {
	if (!getFinalBossAmount()) {
		moveToNextScreen();
	}
}

Screen* getScreen8NextScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen Screen8 = {
	.mLoad = loadScreen8,
	.mUpdate = updateScreen8,
	.mGetNextScreen = getScreen8NextScreen,

};