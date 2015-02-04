#ifndef __GAC_X11CAIRO_XLIB_NATIVE_WINDOW_SERVICE_H
#define __GAC_X11CAIRO_XLIB_NATIVE_WINDOW_SERVICE_H

#include <GacUI.h>
#include "../XlibIncludes.h"
#include "../XlibWindow.h"
#include "../XlibXRecordMouseHookHelper.h"
#include "../../Common/ServicesImpl/PosixAsyncService.h"
#include "XlibNativeCallbackService.h"

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
					XlibXRecordMouseHookHelper* recordHelper;
					XlibWindow* mainWindow;
					vl::collections::List<XlibWindow*> windows;
					bool timerFlag;

					XlibWindow* FindWindow(Window win);
					void DispatchGlobalMouseEvent(const MouseEvent& ev);
					NativeWindowMouseInfo MouseStateMaskToInfo(int x, int y, unsigned int state);
					MouseButton XButtonCodeToButton(unsigned int button);

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
