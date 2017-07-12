#include "pirate.h"

#include <tari/log.h>
#include <tari/animation.h>
#include <tari/memoryhandler.h>
#include <tari/physicshandler.h>
#include <tari/actorhandler.h>
#include <tari/collisionhandler.h>

#include "collision.h"

static struct {
	Animation mAnimation;
	TextureData mTextures[10];
} gData;

typedef struct {
	int mAnimation;
	int mPhysics;
	int mActor;
	int mCollision;
	CollisionData mCollisionData;

} Pirate;

static void hasBeenHit(void* tCaller, void* tCollisionData);

static void loadPirate(void* tData) {
	Pirate* e = tData;
	e->mPhysics = addToPhysicsHandler(makePosition(-30, 200, 2));
	addAccelerationToHandledPhysics(e->mPhysics, makePosition(3, 0, 0));

	e->mAnimation = playAnimationLoop(makePosition(0, 0, 0), gData.mTextures, gData.mAnimation, makeRectangleFromTexture(*gData.mTextures));
	setAnimationBasePositionReference(e->mAnimation, getHandledPhysicsPositionReference(e->mPhysics));

	Collider c = makeColliderFromRect(makeCollisionRect(makePosition(0, 0, 0), makePosition(128, 128, 0)));
	e->mCollisionData.mList = getPirateCollisionList();
	e->mCollision = addColliderToCollisionHandler(getPirateCollisionList(), getHandledPhysicsPositionReference(e->mPhysics), c, hasBeenHit, e, &e->mCollisionData);
}

static void unloadPirate(void* tData) {
	Pirate* e = tData;

	removeFromCollisionHandler(getPirateCollisionList(), e->mCollision);
	removeHandledAnimation(e->mAnimation);
	removeFromPhysicsHandler(e->mPhysics);
}

static void hasBeenHit(void* tCaller, void* tCollisionData) {
	Pirate* e = tCaller;
	CollisionData* colData = tCollisionData;

	(void)e;
	(void)colData;
}

ActorBlueprint PirateBP = {
	.mLoad = loadPirate,
	.mUnload = unloadPirate,
};

void loadPirates() {
	gData.mAnimation = createEmptyAnimation();
	gData.mAnimation.mDuration = 3;
	gData.mAnimation.mFrameAmount = 2;

	loadConsecutiveTextures(gData.mTextures, "assets/sprites/PIRATE.pkg", gData.mAnimation.mFrameAmount);
}

void addNewPirate()
{
	Pirate* e = allocMemory(sizeof(Pirate));
	e->mActor = instantiateActorWithData(PirateBP, e, 1);
}
