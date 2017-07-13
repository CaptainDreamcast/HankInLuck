#include "horseguy.h"

#include <tari/animation.h>
#include <tari/collisionhandler.h>

#include "collision.h"
#include "gamelogic.h"

static struct {
	TextureData mHorseTexture;
	int mHorseAnimation;
	int mCollision;
	CollisionData mCollisionData;
	Position mPosition;

	char mName[100];
} gData;

static void hasBeenHit(void* tCaller, void* tCollisionData);

static void loadHorseGuy(void* tData) {
	(void)tData;

	gData.mPosition = makePosition(300, 100, 2);
	char path[1024];
	sprintf(path, "assets/sprites/%s.pkg", gData.mName);
	gData.mHorseTexture = loadTexture(path);
	gData.mHorseAnimation = playOneFrameAnimationLoop(gData.mPosition, &gData.mHorseTexture);
	
	gData.mCollisionData.mList = getNPCCollisionList();
	Collider c = makeColliderFromRect(makeCollisionRect(makePosition(0,0,0), makePosition(256,128, 1)));
	addColliderToCollisionHandler(getNPCCollisionList(), &gData.mPosition, c, hasBeenHit, NULL, &gData.mCollisionData);
}


static void hasBeenHit(void* tCaller, void* tCollisionData) {
	(void)tCaller;
	(void)tCollisionData;
	moveToNextScreen();
}

ActorBlueprint HorseGuyBP = {
	.mLoad = loadHorseGuy,

};

void setHorseGuyName(char * tName)
{
	strcpy(gData.mName, tName);
}
