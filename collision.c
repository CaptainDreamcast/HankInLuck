#include "collision.h"

#include <tari/collisionhandler.h>

static struct {
	int mHankList;
	int mHankAttackList;
	int mPirateList;
	int mNPCCollisionList;
} gData;

void setupGameCollisions()
{
	gData.mHankList = addCollisionListToHandler();
	gData.mHankAttackList = addCollisionListToHandler();
	gData.mPirateList = addCollisionListToHandler();
	gData.mNPCCollisionList = addCollisionListToHandler();

	addCollisionHandlerCheck(gData.mHankList, gData.mPirateList);
	addCollisionHandlerCheck(gData.mHankAttackList, gData.mPirateList);
	addCollisionHandlerCheck(gData.mHankAttackList, gData.mNPCCollisionList);

}

int getHankCollisionList()
{
	return gData.mHankList;
}

int getPirateCollisionList()
{
	return gData.mPirateList;
}

int getHankAttackCollisionList()
{
	return gData.mHankAttackList;
}

int getNPCCollisionList()
{
	return gData.mNPCCollisionList;
}
