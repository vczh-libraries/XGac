#include "XlibNativeWindowService.h"


namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
                XlibNativeWindowService::XlibNativeWindowService (char const *displayString)
                {
                    this->display = XOpenDisplay(display);
                }

                XlibNativeWindowService::~XlibNativeWindowService ()
                {
                    XCloseDisplay(display);
                }
            }
        }
    }
}