#ifndef __GAC_X11CAIRO_XLIB_COMMON_H
#define __GAC_X11CAIRO_XLIB_COMMON_H

#include "XlibIncludes.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				enum MouseButtons
				{
					X11CAIRO_LBUTTON,
					X11CAIRO_RBUTTON
				};

				bool CheckXdbeExtension(Display*);
				bool CheckXRecordExtension(Display*);
			}
		}
	}
}

#endif
