#ifndef __X11_CAIRO_INCLUDES_H
#define __X11_CAIRO_INCLUDES_H

extern void SetupX11CairoRenderer();

#ifdef GAC_CAIRO_XCB

#include "XCB/XCBNativeController.h"
#include "XCB/XCBCairoWindow.h"

#endif

#endif
