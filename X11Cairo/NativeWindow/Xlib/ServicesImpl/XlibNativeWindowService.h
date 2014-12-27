#ifndef __XLIB_NATIVE_WINDOW_SERVICE_H
#define __XLIB_NATIVE_WINDOW_SERVICE_H

#include "../XlibIncludes.h"
#include <GacUI.h>

namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
				class XlibNativeWindowService: public Object, public virtual INativeWindowService
				{
				protected:
					Display* display;

				public:
					XlibNativeWindowService (const char *displayString = NULL);

					~XlibNativeWindowService ();

					virtual INativeWindow *CreateNativeWindow ();

					virtual void DestroyNativeWindow (INativeWindow *window);

					virtual INativeWindow *GetMainWindow ();

					virtual INativeWindow *GetWindow (Point location);

					virtual void Run (INativeWindow *window);
				};
            }
        }
    }
}

#endif
