#include "screen1.h"

#include <stdio.h>
#include <tari/input.h>

#include "bg.h"
#include "hank.h"
#include "narrator.h"
#include "enemyhandler.h"
#include "collision.h"
#include "gamelogic.h"
#include "screen2.h"
#include "titlescreen.h"

static void loadScreen1() {
	setHankName("GOLD");
	setNarratorText("Hank had found a head-sized chunk of gold, yet gold-resistant pirates were abound. He went right in flight.");
	setCurrentScreen(&Screen1);
	setNextScreen(&Screen2);

	setupGameCollisions();
	instantiateActor(BackgroundBP);
	instantiateActor(HankBP);
	instantiateActor(NarratorBP);
	instantiateActor(EnemyHandlerBP);
	setHankSupposedToGoRight();
	setHankPosition(makePosition(320, 150, 2));
}

Screen* getScreen1NextScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen Screen1 = {
	.mLoad = loadScreen1,
	.mGetNextScreen = getScreen1NextScreen,

};