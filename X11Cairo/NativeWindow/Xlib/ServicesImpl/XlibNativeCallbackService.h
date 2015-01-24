#ifndef __GAC_X11CAIRO_XLIB_NATIVE_CALLBACK_SERVICE_H
#define __GAC_X11CAIRO_XLIB_NATIVE_CALLBACK_SERVICE_H

#include <GacUI.h>
#include "../XlibIncludes.h"


namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				class XlibNativeCallbackService: public Object, public INativeCallbackService
				{
				protected:
					collections::List<INativeControllerListener*> listeners;
					bool flag;

				public:
					virtual bool					InstallListener(INativeControllerListener* listener);
					virtual bool					UninstallListener(INativeControllerListener* listener);

					void CheckTimer();
					void SetTimer();
					void MouseUpEvent(MouseButton button, Point position);
					void MouseDownEvent(MouseButton button, Point position);
					void MouseMoveEvent(Point position);
				};
			}
		}
	}
}

#endif
