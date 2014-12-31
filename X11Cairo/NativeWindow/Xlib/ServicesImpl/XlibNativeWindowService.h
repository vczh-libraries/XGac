#ifndef __XLIB_NATIVE_WINDOW_SERVICE_H
#define __XLIB_NATIVE_WINDOW_SERVICE_H

#include "../XlibIncludes.h"
#include <GacUI.h>
#include "../XlibCairoWindow.h"
#include "../../Common/ServiceImpl/PosixAsyncService.h"

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
					PosixAsyncService* asyncService;
					vl::collections::List<XlibCairoWindow*> windows;

				public:
					XlibNativeWindowService (Display* display);

					virtual ~XlibNativeWindowService ();

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
