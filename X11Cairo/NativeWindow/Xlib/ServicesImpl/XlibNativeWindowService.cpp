#include "XlibNativeWindowService.h"
#include "../../Common/ServiceImpl/PosixAsyncService.h"


namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				XlibNativeWindowService::XlibNativeWindowService(Display *display, PosixAsyncService* asyncService)
				{
					this->display = display;
					this->asyncService = asyncService;
				}

				XlibNativeWindowService::~XlibNativeWindowService()
				{
				}

				INativeWindow *XlibNativeWindowService::CreateNativeWindow()
				{
					XlibCairoWindow *window = new XlibCairoWindow(display);
					asyncService->
					windows.Add(window);
				}

				void XlibNativeWindowService::DestroyNativeWindow(INativeWindow *window)
				{
					if (window)
					{
						windows.Remove(window);
						delete window;
					}
				}

				void XlibNativeWindowService::GetMainWindow()
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
					XlibCairoWindow* window = dynamic_cast<XlibCairoWindow*>(window)
					if(!window)
					{
						throw Exception(L"Invalid Window Type");
					}
					do
					{
						XWindowEvent(window->GetDisplay(), window->GetWindow(), 0, event);
						asyncService->ExecuteAsyncTasks();
					}
				}
			}
		}
	}
}