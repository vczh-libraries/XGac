#ifndef __XLIB_NATIVE_CONTROLLER
#define __XLIB_NATIVE_CONTROLLER

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
