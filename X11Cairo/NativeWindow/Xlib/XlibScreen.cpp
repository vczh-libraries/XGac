#include "XlibScreen.h"


namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
				XlibScreen::XlibScreen(Display* display, Screen* screen, int id)
					: display (display),
					screen (screen),
					id (id)
				{

				}

				Rect XlibScreen::GetBounds()
				{
					//TODO
					return GetClientBounds();
				}

				Rect XlibScreen::GetClientBounds()
				{
					return Rect(0, 0, XWidthOfScreen(screen), XHeightOfScreen(screen));
				}

				WString XlibScreen::GetName()
				{
					return WString(L"Screen ") + WString(XScreenNumberOfScreen(screen));
				}

				bool XlibScreen::IsPrimary()
				{
					//TODO
					return true;
				}
			}
		}
	}
}

