#ifndef __GAC_X11CAIRO_XLIB_XRECORD_MOUSE_HOOK_HELPER_H
#define __GAC_X11CAIRO_XLIB_XRECORD_MOUSE_HOOK_HELPER_H

#include <GacUI.h>
#include "XlibIncludes.h"

extern "C"
{
#include <X11/Xmd.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/extensions/record.h>
}

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				class XlibXRecordMouseHookHelper: public Object
				{
				protected:
					vl::collections::List<MouseEvent> hookEvents;
					XRecordContext recordContext;
					Display *ctrlDisplay, *dataDisplay;
					bool capturing;

					MouseEvent DataToEvent(xEvent* ev);

				public:
					XlibXRecordMouseHookHelper(const char*);
					~XlibXRecordMouseHookHelper();
					void Update();
					void ProcessEvents(Func<void(MouseEvent)>);
					void StartCapture();
					void EndCapture();
					bool IsCapturing();

					void AddData(xEvent* ev);
				};
			}
		}
	}
}

#endif
