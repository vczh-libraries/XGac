#include "XlibNativeWindowService.h"
#include "../XlibNativeController.h"

#include <unistd.h>

using namespace vl::presentation;

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				XlibNativeWindowService::XlibNativeWindowService(Display* display, PosixAsyncService* asyncService, XlibNativeCallbackService* callbackService):
					display(display),
					asyncService(asyncService),
					callbackService(callbackService)
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
					XEvent event;
					XlibCairoWindow* actualWindow = dynamic_cast<XlibCairoWindow*>(window);

					Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", XLIB_FALSE);
					XSetWMProtocols(actualWindow->GetDisplay(), actualWindow->GetWindow(), &WM_DELETE_WINDOW, 1);

					if(!window)
					{
						throw Exception(L"Invalid Window Type");
					}
					while(true)
					{
						while(XPending(actualWindow->GetDisplay()))
						{
							XNextEvent(actualWindow->GetDisplay(), &event);
							switch(event.type)
							{
								case ClientMessage:
									XFlush(actualWindow->GetDisplay());
									return;
								default:
									break;
							}
						}

						asyncService->ExecuteAsyncTasks();
						callbackService->CheckTimer();
						XFlush(actualWindow->GetDisplay());

						pause();
					}
				}
			}
		}
	}
}
