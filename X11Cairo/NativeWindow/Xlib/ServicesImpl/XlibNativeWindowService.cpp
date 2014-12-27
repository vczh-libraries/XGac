#include "XlibNativeWindowService.h"


namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
                XlibNativeWindowService::XlibNativeWindowService (char const *display)
                {
                    this->display = XOpenDisplay(display);
                }

                XlibNativeWindowService::~XlibNativeWindowService ()
                {
                    XCloseDisplay(display)
                }
            }
        }
    }
}