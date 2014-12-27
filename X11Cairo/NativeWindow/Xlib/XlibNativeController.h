#ifndef __XLIB_NATIVE_CONTROLLER
#define __XLIB_NATIVE_CONTROLLER

#include <GacUI.h>

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
			    extern INativeController *CreateXCBCairoNativeController (const char *displayname = NULL);
			    extern void DestroyXCBCairoNativeController (INativeController *controller);
			}
		}
	}
}

#endif
