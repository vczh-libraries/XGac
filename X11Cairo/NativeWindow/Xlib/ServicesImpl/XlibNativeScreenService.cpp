#include "XlibNativeScreenService.h"
#include "../XlibScreen.h"
#include "../XlibWindow.h"

namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
				XlibNativeScreenService::XlibNativeScreenService(Display* display)
					: display (display)
				{
				}

				vint XlibNativeScreenService::GetScreenCount()
				{
					return XScreenCount(display);
				}

				INativeScreen* XlibNativeScreenService::GetScreen(vint index)
				{
					return new XlibScreen(display, XScreenOfDisplay(display, index), index);
				}

                INativeScreen* XlibNativeScreenService::GetScreen(INativeWindow* window)
				{
					XlibWindow *actualWindow = dynamic_cast<XlibWindow*>(window);
					if(actualWindow)
					{
						XWindowAttributes attr;
						XGetWindowAttributes(display, actualWindow->GetWindow(), &attr);
						return new XlibScreen(display, attr.screen, XScreenNumberOfScreen(attr.screen));
					}

					return NULL;
				}
            }
        }
    }
}
