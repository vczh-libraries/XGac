#ifndef __XLIB_NATIVE_SCREEN_SERVICE_H
#define __XLIB_NATIVE_SCREEN_SERVICE_H

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
                public:
                    virtual vint					GetScreenCount();
                    virtual INativeScreen*			GetScreen(vint index);
                    virtual INativeScreen*			GetScreen(INativeWindow* window);
                };
            }
        }
    }
}

#endif
