#include "X11CairoSetup.h"

#ifndef GAC_CAIRO_XCB
#include "Xlib/XlibNativeController.h"

void SetupX11CairoRenderer(const char* displayname)
{
	INativeController* controller = CreateXlibCairoNativeController(displayname);
	SetCurrentController(controller);


	DestroyXlibCairoNativeController(controller);
	return 0;
}

#endif