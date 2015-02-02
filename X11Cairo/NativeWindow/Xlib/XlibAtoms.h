#ifndef __GAC_X11CAIRO_XLIB_ATOMS_H
#define __GAC_X11CAIRO_XLIB_ATOMS_H

#include <Vlpp.h>
#include "XlibIncludes.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				struct XlibAtoms
				{
					static vl::collections::Dictionary<vl::AString, Atom> map;
					static Atom WM_DELETE_WINDOW;
					static Atom _MOTIF_WM_HINTS;
					static Atom _NET_WM_WINDOW_TYPE;
					static Atom _NET_WM_WINDOW_TYPE_NORMAL;
					static Atom _NET_WM_WINDOW_TYPE_POPUP_MENU;

					static void Initialize(Display* display);
				};
			}
		}
	}
}


#endif
