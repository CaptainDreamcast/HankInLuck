#include "screen4.h"

#include <stdio.h>
#include <tari/input.h>

#include "hank.h"
#include "narrator.h"
#include "enemyhandler.h"
#include "collision.h"
#include "gamelogic.h"
#include "bg.h"
#include "horseguy.h"
#include "screen5.h"
#include "smashscreen.h"
#include "titlescreen.h"

static void loadScreen4() {
	setHankName("HORSE");
	setNarratorText("\"If only\", Hank lost himself in thought, \"I could get a drink after this drought.\"");
	setCurrentScreen(&Screen4);
	setNextScreen(&SmashScreen);
	setSmashScreenNarrationAndAfterScreen("Lucky as Hank ever was, he traded his horse for a milk-filled glass.", &Screen5);

	setupGameCollisions();
	instantiateActor(BackgroundBP);
	instantiateActor(HankBP);
	instantiateActor(NarratorBP);
	instantiateActor(EnemyHandlerBP);

	setHorseGuyName("MILK");
	instantiateActor(HorseGuyBP);
}

Screen* getScreen4NextScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen Screen4 = {
	.mLoad = loadScreen4,
	.mGetNextScreen = getScreen4NextScreen,

};