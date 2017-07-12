#include <tari/framerateselectscreen.h>
#include <tari/pvr.h>
#include <tari/physics.h>
#include <tari/file.h>
#include <tari/drawing.h>
#include <tari/log.h>
#include <tari/wrapper.h>
#include <tari/system.h>
#include <tari/stagehandler.h>
#include <tari/logoscreen.h>
#include <tari/collisionhandler.h>

#include "titlescreen.h"
#include "screen1.h"
#include "screen3.h"
#include "screen4.h"
#include "screen5.h"
#include "screen6.h"
#include "screen7.h"
#include "screen8.h"
#include "congratsscreen.h"

#ifdef DREAMCAST
KOS_INIT_FLAGS(INIT_DEFAULT);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);
#endif


void exitGame() {
	shutdownTariWrapper();

#ifdef DEVELOP
	abortSystem();
#else
	returnToMenu();
#endif
}

void setMainFileSystem() {
#ifdef DEVELOP
	setFileSystem("/pc");
#else
	setFileSystem("/rd");
#endif
}

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	setGameName("HANK IN LUCK");
	setScreenSize(640, 480);
	
	initTariWrapperWithDefaultFlags();
	setFont("$/rd/fonts/segoe.hdr", "$/rd/fonts/segoe.pkg");

	logg("Check framerate");
	FramerateSelectReturnType framerateReturnType = selectFramerate();
	if (framerateReturnType == FRAMERATE_SCREEN_RETURN_ABORT) {
		exitGame();
	}

	setMainFileSystem();

	setStageHandlerNoDelayedLoading();
	setScreenAfterWrapperLogoScreen(&TitleScreen);
	startScreenHandling(getLogoScreenFromWrapper());

	exitGame();

	return 0;
}


// TODO: find out why main doesn't work
int wmain(int argc, char** argv) {
	return main(argc, argv);
}


