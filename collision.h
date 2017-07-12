#pragma once

typedef struct {
	int mList;
} CollisionData;

void setupGameCollisions();

int getHankCollisionList();
int getPirateCollisionList();
int getHankAttackCollisionList();
int getNPCCollisionList();
