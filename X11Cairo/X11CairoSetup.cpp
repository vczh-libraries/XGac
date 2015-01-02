#include "X11CairoSetup.h"
#include "GraphicsElement/X11CairoResourceManager.h"
#include "GraphicsElement/GuiGraphicsX11Cairo.h"
#include <locale.h>

#ifndef GAC_CAIRO_XCB
#include "NativeWindow/Xlib/XlibNativeController.h"

void SetupX11CairoRenderer(const char* displayname)
{
	setlocale(LC_ALL, "");

	INativeController* controller = vl::presentation::x11cairo::xlib::CreateXlibCairoNativeController(displayname);
	SetCurrentController(controller);

	vl::presentation::x11cairo::RegisterX11CairoResourceManager();
	vl::presentation::elements_x11cairo::RegisterX11CairoElementRenderers(); 

	vl::presentation::x11cairo::xlib::X11CairoMain();

	vl::presentation::x11cairo::xlib::DestroyXlibCairoNativeController(controller);
}

#endif
