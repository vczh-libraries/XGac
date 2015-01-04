#ifndef __GAC_X11CAIRO_XLIB_NATIVE_SCREEN_SERVICE_H
#define __GAC_X11CAIRO_XLIB_NATIVE_SCREEN_SERVICE_H

#include <GacUI.h>
#include "../XlibIncludes.h"

namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
                class XlibNativeScreenService: public Object, public INativeScreenService
                {
				protected:
					Display* display;
                public:
					XlibNativeScreenService(Display* display);
                    virtual vint					GetScreenCount();
                    virtual INativeScreen*			GetScreen(vint index);
                    virtual INativeScreen*			GetScreen(INativeWindow* window);
                };
            }
        }
    }
}

#endif
