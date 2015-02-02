#include "XlibAtoms.h"

#define DEFINE_ATOM(x) \
	Atom XlibAtoms::x = XLIB_NONE;

#define INIT_ATOM(x) \
	x = XInternAtom(display, #x, XLIB_FALSE); \
	map.Add(#x, x);

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				vl::collections::Dictionary<vl::AString, Atom> XlibAtoms::map;

				DEFINE_ATOM(WM_DELETE_WINDOW);
				DEFINE_ATOM(_MOTIF_WM_HINTS);
				DEFINE_ATOM(_NET_WM_WINDOW_TYPE);
				DEFINE_ATOM(_NET_WM_WINDOW_TYPE_NORMAL);
				DEFINE_ATOM(_NET_WM_WINDOW_TYPE_POPUP_MENU);

				void XlibAtoms::Initialize(Display* display)
				{
					static bool initialized = false;
					if(!initialized)
					{
						INIT_ATOM(WM_DELETE_WINDOW);
						INIT_ATOM(_MOTIF_WM_HINTS);
						INIT_ATOM(_NET_WM_WINDOW_TYPE);
						INIT_ATOM(_NET_WM_WINDOW_TYPE_NORMAL);
						INIT_ATOM(_NET_WM_WINDOW_TYPE_POPUP_MENU);

						initialized = true;
					}
				}
			}
		}
	}
}
