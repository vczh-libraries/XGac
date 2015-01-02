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
			}
		}
	}
}
