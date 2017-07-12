#include "screen2.h"

#include <stdio.h>
#include <tari/input.h>

#include "bg.h"
#include "hank.h"
#include "narrator.h"
#include "enemyhandler.h"
#include "collision.h"
#include "gamelogic.h"
#include "horseguy.h"
#include "screen3.h"
#include "smashscreen.h"
#include "titlescreen.h"

static void loadScreen2() {
	setHankName("GOLD");
	setNarratorText("Hank discovered a man with horse in tow, that the horse would be Hank's he did not know.");
	setCurrentScreen(&Screen2);
	setNextScreen(&SmashScreen);
	setSmashScreenNarrationAndAfterScreen("With a clunk Hank got his horse, inside his heart was no remorse.", &Screen3);

	setupGameCollisions();
	instantiateActor(BackgroundBP);
	instantiateActor(HankBP);
	instantiateActor(NarratorBP);
	instantiateActor(EnemyHandlerBP);

	setHorseGuyName("HORSE");
	instantiateActor(HorseGuyBP);

}

Screen* getScreen2NextScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen Screen2 = {
	.mLoad = loadScreen2,
	.mGetNextScreen = getScreen2NextScreen,

};