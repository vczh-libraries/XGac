#ifndef __X11_X11CAIRO_CAIRO_INCLUDES_H
#define __X11_X11CAIRO_CAIRO_INCLUDES_H

// Macros:
// GAC_X11_XCB: Use XCB for X11 client library
// GAC_X11_DOUBLEBUFFER: Use Xdbe Based Double Buffer
// GAC_X11_CAIRO_OPENGL: Use OpenGL and Cairo_GL (Ignore GAC_X11_DOUBLEBUFFER if selected)

#ifndef GAC_X11_XCB

#include "NativeWindow/Xlib/XlibNativeController.h"
#include "NativeWindow/Xlib/XlibCairoWindow.h"
#include "X11CairoSetup.h"

#endif

#endif
