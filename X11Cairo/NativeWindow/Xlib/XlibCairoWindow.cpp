#include "XlibCairoWindow.h"

namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
                void XlibCairoWindow::Show ()
                {
                    XMapWindow(display, window);
                }

                void XlibCairoWindow::Hide ()
                {
                    XUnmapWindow(display, window);
                }
            }
        }
    }
}

