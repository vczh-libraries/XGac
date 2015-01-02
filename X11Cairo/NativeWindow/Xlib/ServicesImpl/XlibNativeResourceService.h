#ifndef __GAC_X11CAIRO_XLIB_NATIVE_RESOURCE_SERVICE_H
#define __GAC_X11CAIRO_XLIB_NATIVE_RESOURCE_SERVICE_H

#include <GacUI.h>

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				class XlibNativeResourceService: public Object, public INativeResourceService
				{
					INativeCursor*			GetSystemCursor(INativeCursor::SystemCursorType type);
					INativeCursor*			GetDefaultSystemCursor();

					FontProperties			GetDefaultFont();
					void					SetDefaultFont(const FontProperties& value);

				};
			}
		}
	}
}


#endif

