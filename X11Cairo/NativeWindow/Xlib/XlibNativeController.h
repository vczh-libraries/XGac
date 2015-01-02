#ifndef __GAC_X11CAIRO_XLIB_NATIVE_CONTROLLER_H
#define __GAC_X11CAIRO_XLIB_NATIVE_CONTROLLER_H

#include <GacUI.h>

using namespace vl::presentation;

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				extern INativeController *CreateXlibCairoNativeController(const char *displayname = NULL);

				extern void DestroyXlibCairoNativeController(INativeController *controller);

				extern void X11CairoMain();
			}
		}
	}
}

#endif
