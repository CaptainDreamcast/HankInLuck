#include "enemyhandler.h"

#include <tari/timer.h>

#include "door.h"
#include "pirate.h"

static struct {
	int mDoor;

	int mIsGeneratingPirates;

	Duration mGenerateNow;
	Duration mGenerateDuration;
} gData;

static void letPiratesIn(void* tCaller) {
	(void)tCaller;
	removeActor(gData.mDoor);
	gData.mIsGeneratingPirates = 1;
}

static void loadEnemyHandler(void* tData) {
	(void)tData;
	gData.mDoor = instantiateActor(DoorBP);
	gData.mIsGeneratingPirates = 0;
	gData.mGenerateDuration = 31;
	gData.mGenerateNow = gData.mGenerateDuration;
	loadPirates();

	addTimerCB(600, letPiratesIn, NULL);
}

static void updateEnemyHandler(void* tData) {
	(void)tData;

	if (!gData.mIsGeneratingPirates) return;

	if (handleDurationAndCheckIfOver(&gData.mGenerateNow, gData.mGenerateDuration)) {
		addNewPirate();
		gData.mGenerateNow = 0;
	}

}

ActorBlueprint EnemyHandlerBP = {
	.mLoad = loadEnemyHandler,
	.mUpdate = updateEnemyHandler,
};