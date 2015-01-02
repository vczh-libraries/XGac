#ifndef __GAC_X11CAIRO_XLIB_NATIVE_WINDOW_SERVICE_H
#define __GAC_X11CAIRO_XLIB_NATIVE_WINDOW_SERVICE_H

#include <GacUI.h>
#include "../XlibIncludes.h"
#include "../XlibCairoWindow.h"
#include "XlibNativeCallbackService.h"
#include "../../Common/ServicesImpl/PosixAsyncService.h"

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
					XlibNativeCallbackService* callbackService;
					vl::collections::List<XlibCairoWindow*> windows;
					bool timerFlag;

				public:
					XlibNativeWindowService (Display* display, PosixAsyncService* asyncService, XlibNativeCallbackService* callbackService);

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
