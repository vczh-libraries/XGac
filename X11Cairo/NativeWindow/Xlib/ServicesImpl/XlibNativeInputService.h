#ifndef __XLIB_NATIVE_INPUT_SERVICE_H
#define __XLIB_NATIVE_INPUT_SERVICE_H

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
				class XlibNativeInputService: public Object, public INativeInputService
				{
					virtual void					StartHookMouse();
					virtual void					StopHookMouse();
					virtual bool					IsHookingMouse();
					
					virtual void					StartTimer();
					virtual void					StopTimer();
					virtual bool					IsTimerEnabled();
					
					virtual bool					IsKeyPressing(vint code);
					virtual bool					IsKeyToggled(vint code);
					
					virtual WString					GetKeyName(vint code);
					virtual vint					GetKey(const WString& name);
				};
			}
		}
	}
}

#endif
