#include "XlibNativeInputService.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				void XlibNativeInputService::StartHookMouse()
				{
					//TODO
				}

				void XlibNativeInputService::StopHookMouse()
				{
					//TODO

				}

				bool XlibNativeInputService::IsHookingMouse()
				{
					//TODO
					return false;
				}

				void XlibNativeInputService::StartTimer()
				{
					//TODO
				}

				void XlibNativeInputService::StopTimer()
				{
					//TODO
				}

				bool XlibNativeInputService::IsTimerEnabled()
				{
					//TODO
					return false;
				}

				bool XlibNativeInputService::IsKeyPressing(vint code)
				{
					//TODO
					return false;
				}

				bool XlibNativeInputService::IsKeyToggled(vint code)
				{
					//TODO
					return false;
				}

				WString XlibNativeInputService::GetKeyName(vint code)
				{
					//TODO
					return WString();
				}

				vint XlibNativeInputService::GetKey(const WString &name)
				{
					//TODO
					return 0;
				}
			}
		}
	}
}