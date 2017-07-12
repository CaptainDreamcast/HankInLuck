#include "screen5.h"

#include <stdio.h>
#include <tari/input.h>

#include "hank.h"
#include "narrator.h"
#include "enemyhandler.h"
#include "collision.h"
#include "gamelogic.h"
#include "bg.h"
#include "horseguy.h"
#include "screen6.h"
#include "smashscreen.h"
#include "titlescreen.h"

static void loadScreen5() {
	setHankName("MILK");
	setNarratorText("Seeing a goose-owning ghost as he chugged, he thought \"Ghosts aren't real\" and shrugged.");
	setCurrentScreen(&Screen5);
	setNextScreen(&SmashScreen);
	setSmashScreenNarrationAndAfterScreen("\"How lucky\", Hank pondered aloud, \"a lone goose!\" and flew away from the pursuing crowd.", &Screen6);

	setupGameCollisions();
	instantiateActor(BackgroundBP);
	instantiateActor(HankBP);
	instantiateActor(NarratorBP);
	instantiateActor(EnemyHandlerBP);

	setHorseGuyName("GOOSE");
	instantiateActor(HorseGuyBP);
}

Screen* getScreen5NextScreen() {
	
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen Screen5 = {
	.mLoad = loadScreen5,
	.mGetNextScreen = getScreen5NextScreen,

};