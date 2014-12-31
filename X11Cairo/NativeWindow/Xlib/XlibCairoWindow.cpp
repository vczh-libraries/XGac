#include "XlibCairoWindow.h"

namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
                XlibCairoWindow::XlibCairoWindow(Display *display)
                {
                    this->display = display;
                    window = XCreateWindow(display, XRootWindow(display, 0), 0, 0, 200, 200, CopyFromParent, InputOutput, CopyFromParent, CopyFromParent, 0, NULL);
                }

                XlibCairoWindow::~XlibCairoWindow()
                {
                    XDestroyWindow(display, window);
                }

                Window XlibCairoWindow::GetWindow()
                {
                    return window;
                }

                Display* XlibCairoWindow::GetDisplay()
                {
                    return display;
                }

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

