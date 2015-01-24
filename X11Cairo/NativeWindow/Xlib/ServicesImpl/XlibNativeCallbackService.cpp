#include "XlibNativeCallbackService.h"

using namespace vl::collections;

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				bool XlibNativeCallbackService::InstallListener(INativeControllerListener* listener)
				{
					listeners.Add(listener);
					return true;
				}
				bool XlibNativeCallbackService::UninstallListener(INativeControllerListener* listener)
				{
					return listeners.Remove(listener);
				}

				void XlibNativeCallbackService::SetTimer()
				{
					flag = true;
				}

				void XlibNativeCallbackService::CheckTimer()
				{
					if(flag)
					{
						flag = false;
						FOREACH( INativeControllerListener*, i, listeners)
						{
							i->GlobalTimer();
						}
					}
				}
				void XlibNativeCallbackService::MouseUpEvent(MouseButton button, Point position)
				{
					switch(button)
					{
						case MouseButton::LBUTTON:
							FOREACH( INativeControllerListener*, i, listeners)
							{
								i->LeftButtonDown(position);
							}
							break;

						case MouseButton::RBUTTON:
							FOREACH( INativeControllerListener*, i, listeners)
							{
								i->RightButtonDown(position);
							}
							break;
					}
				}
				void XlibNativeCallbackService::MouseDownEvent(MouseButton button, Point position)
				{
					switch(button)
					{
						case MouseButton::LBUTTON:
							FOREACH( INativeControllerListener*, i, listeners)
							{
								i->LeftButtonUp(position);
							}
							break;

						case MouseButton::RBUTTON:
							FOREACH( INativeControllerListener*, i, listeners)
							{
								i->RightButtonUp(position);
							}
							break;
					}

				}
				void XlibNativeCallbackService::MouseMoveEvent(Point position)
				{
					FOREACH( INativeControllerListener*, i, listeners)
					{
						i->MouseMoving(position);
					}
				}
			}
		}
	}
}
