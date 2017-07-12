#pragma once

#include <tari/actorhandler.h>
#include <tari/geometry.h>

extern ActorBlueprint HankBP;

void setHankName(char* tName);
void setHankSupposedToGoRight();
void setHankPosition(Position tPosition);
void setHankEvasionLevel();