#include "box.h"

#include <tari/animation.h>
#include <tari/physicshandler.h>
#include <tari/collisionhandler.h>
#include <tari/math.h>

#include "collision.h"

static struct {

	TextureData mTextureData;
	Animation mAnimation;
} gData;

void loadBoxes() {
	gData.mTextureData = loadTexture("assets/sprites/BOX.pkg");
	gData.mAnimation = createOneFrameAnimation();
}

typedef struct {
	int mPhysics;
	int mAnimation;
	int mCollision;
	CollisionData mCollisionData;
	Collider mCollider;
	int mActor;

} Box;

static void loadBox(void* tData) {
	Box* e = tData;

	double x = 700;
	double y = randfrom(-64, 480);
	double z = 2 + (y - (-64)) / (480 - (-64.0));

	e->mPhysics = addToPhysicsHandler(makePosition(x, y, z));
	addAccelerationToHandledPhysics(e->mPhysics, makePosition(-10, 0, 0));

	e->mAnimation = playAnimationLoop(makePosition(0,0,0), &gData.mTextureData, gData.mAnimation, makeRectangleFromTexture(gData.mTextureData));
	setAnimationBasePositionReference(e->mAnimation, getHandledPhysicsPositionReference(e->mPhysics));

	e->mCollisionData.mList = getPirateCollisionList();
	e->mCollider = makeColliderFromRect(makeCollisionRect(makePosition(0, 0, 0), makePosition(64, 64, 0)));
	e->mCollision = addColliderToCollisionHandler(getPirateCollisionList(), getHandledPhysicsPositionReference(e->mPhysics), e->mCollider, NULL, NULL, &e->mCollisionData);
}

static void updateBox(void* tData) {
	Box* e = tData;

	if (getHandledPhysicsPositionReference(e->mPhysics)->x < -100) {
		removeActor(e->mActor);
	}
}

static void unloadBox(void* tData) {
	Box* e = tData;

	removeFromCollisionHandler(getPirateCollisionList(), e->mCollision);
	destroyCollider(&e->mCollider);

	removeHandledAnimation(e->mAnimation);

	removeFromPhysicsHandler(e->mPhysics);
}

ActorBlueprint BoxBP = {
	.mLoad = loadBox,
	.mUnload = unloadBox,
	.mUpdate = updateBox,
};

void addBox()
{
	Box* e = allocMemory(sizeof(Box));
	e->mActor = instantiateActorWithData(BoxBP, e, 1);
}
