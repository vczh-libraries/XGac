#ifndef __GAC_X11CAIRO_XLIB_MOUSE_RECORD_HELPER_H
#define __GAC_X11CAIRO_XLIB_MOUSE_RECORD_HELPER_H

#include <GacUI.h>
#include "XlibIncludes.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				class XlibMouseRecordHelper: public Object
				{
				protected:
					vl::collections::List<Point> hookEvents;
					XRecordContext recordContext;
					Display *ctrl_display, *data_display;
					bool capturing;

				public:
					XlibMouseRecordHelper(const char*);
					~XlibMouseRecordHelper();
					void Update();
					Point GetEvent();
					int EventCount();
					void StartCapture();
					void EndCapture();
					bool IsCapturing();
				};
			}
		}
	}
}

#endif
