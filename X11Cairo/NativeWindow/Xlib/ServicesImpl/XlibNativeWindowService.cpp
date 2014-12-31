#include "XlibNativeWindowService.h"
#include "../XlibNativeController.h"
#include "../../Common/ServiceImpl/PosixAsyncService.h"

using namespace vl::presentation;

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				XlibNativeWindowService::XlibNativeWindowService(Display* display, PosixAsyncService* asyncService):
					display(display),
					asyncService(asyncService)
				{
				}

				XlibNativeWindowService::~XlibNativeWindowService()
				{
				}

				INativeWindow *XlibNativeWindowService::CreateNativeWindow()
				{
					XlibCairoWindow *window = new XlibCairoWindow(display);
					windows.Add(window);

					return window;
				}

				void XlibNativeWindowService::DestroyNativeWindow(INativeWindow *window)
				{
					if (window)
					{
						XlibCairoWindow* actualWindow = dynamic_cast<XlibCairoWindow*>(window);
						if(actualWindow)
						{
							windows.Remove(actualWindow);
							delete window;
						}
						else
						{
							throw Exception(L"Wrong Window Type");
						}
					}
				}

				INativeWindow* XlibNativeWindowService::GetMainWindow()
				{
					if(windows.Count() > 0)
					{
						return windows[0];
					}
					else return NULL;
				}

				INativeWindow* XlibNativeWindowService::GetWindow(Point location)
				{
					//TODO
					return NULL;
				}

				void XlibNativeWindowService::Run(INativeWindow *window)
				{
					XEvent* event;
					XlibCairoWindow* actualWindow = dynamic_cast<XlibCairoWindow*>(window);
					if(!window)
					{
						throw Exception(L"Invalid Window Type");
					}
					while(true)
					{
						XWindowEvent(actualWindow->GetDisplay(), actualWindow->GetWindow(), 0, event);
						asyncService->ExecuteAsyncTasks();
						XFlush(actualWindow->GetDisplay());
					}
				}
			}
		}
	}
}
