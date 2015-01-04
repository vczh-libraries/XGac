#ifndef __GAC_X11CAIRO_XLIB_SCREEN_H
#define __GAC_X11CAIRO_XLIB_SCREEN_H

#include <GacUI.h>
#include "XlibIncludes.h"

namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
				class XlibScreen: public Object, public INativeScreen
				{
				protected:
					Display* display;
					Screen* screen;
				public:
					XlibScreen(Display* display, Screen* screen);
					Rect				GetBounds();
					Rect				GetClientBounds();
					WString				GetName();
					bool				IsPrimary();
				};
            }
        }
    }
}

#endif
