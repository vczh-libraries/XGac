#ifndef __GAC_X11CAIRO_XLIB_INCLUDES_H
#define __GAC_X11CAIRO_XLIB_INCLUDES_H

extern "C"
{
#include <X11/Xlib.h>
#include <X11/Xutil.h>
}

const Bool XLIB_TRUE = True;
const Bool XLIB_FALSE = False;
const Status XLIB_SUCCESS = Success;
const Status XLIB_NONE = None;

#undef True
#undef False
#undef Success
#undef None

#include "XlibCommons.h"

#endif
