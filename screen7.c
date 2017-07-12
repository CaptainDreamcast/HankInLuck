#include "screen7.h"

#include <stdio.h>
#include <tari/input.h>

#include "hank.h"
#include "narrator.h"
#include "enemyhandler.h"
#include "collision.h"
#include "gamelogic.h"
#include "bg.h"
#include "horseguy.h"
#include "screen8.h"
#include "smashscreen.h"
#include "titlescreen.h"

static void loadScreen7() {
	setHankName("GOOSE");
	setNarratorText("As the journey's end was closing near, Hank's trading skills now knew no peer.");
	setCurrentScreen(&Screen7);
	setNextScreen(&SmashScreen);
	setSmashScreenNarrationAndAfterScreen("It was the usual routine. A stone for a goose, Hank's conscience was clean.", &Screen8);

	setupGameCollisions();
	instantiateActor(BackgroundBP);
	instantiateActor(HankBP);
	instantiateActor(NarratorBP);
	instantiateActor(EnemyHandlerBP);

	setHorseGuyName("STONE");
	instantiateActor(HorseGuyBP);
}

Screen* getScreen7NextScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen Screen7 = {
	.mLoad = loadScreen7,
	.mGetNextScreen = getScreen7NextScreen,

};