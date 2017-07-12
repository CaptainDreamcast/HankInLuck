#include "boxgenerator.h"

#include <tari/animation.h>
#include <tari/math.h>

#include "box.h"

static struct {

	Duration mNow;
	Duration mNext;

} gData;

static void loadBoxGenerator(void* tData) {
	loadBoxes();
	gData.mNow = 0;
	gData.mNext = randfromInteger(10, 60);
}

static void updateBoxGenerator(void* tData) {

	if (handleDurationAndCheckIfOver(&gData.mNow, gData.mNext)) {
		addBox();
		gData.mNow = 0;
		gData.mNext = randfromInteger(30, 60);
	}
}

ActorBlueprint BoxGeneratorBP = {
	.mLoad = loadBoxGenerator,
	.mUpdate = updateBoxGenerator,
};