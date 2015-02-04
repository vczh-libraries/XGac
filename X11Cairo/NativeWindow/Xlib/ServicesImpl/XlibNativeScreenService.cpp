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
					: display (display), count(XScreenCount(display)), screens(new INativeScreen*[XScreenCount(display)])
				{
					for(int i = 0; i < count; i++)
					{
						screens[i] = new XlibScreen(display, XScreenOfDisplay(display, i), i);
					}
				}

				XlibNativeScreenService::~XlibNativeScreenService()
				{
					for(int i = 0; i < count; i++)
					{
						delete screens[i];
					}

					delete[] screens;
				}

				vint XlibNativeScreenService::GetScreenCount()
				{
					return count;
				}

				INativeScreen* XlibNativeScreenService::GetScreen(vint index)
				{
					return screens[index];
				}

                INativeScreen* XlibNativeScreenService::GetScreen(INativeWindow* window)
				{
					XlibWindow *actualWindow = dynamic_cast<XlibWindow*>(window);
					if(actualWindow)
					{
						XWindowAttributes attr;
						XGetWindowAttributes(display, actualWindow->GetWindow(), &attr);
						return screens[XScreenNumberOfScreen(attr.screen)];
					}

					return NULL;
				}
            }
        }
    }
}
