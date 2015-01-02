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
					struct itimerval timer;
					timer.it_interval.tv_usec = timerInterval;
					timer.it_interval.tv_sec = 0;
					timer.it_value.tv_usec = timerInterval;
					timer.it_value.tv_sec = 0;
					if(setitimer(ITIMER_REAL, &timer, NULL))
						throw Exception(L"Failed to setup timer");
				}

				void XlibNativeInputService::StopTimer()
				{
					setitimer(ITIMER_REAL, NULL, NULL);
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
