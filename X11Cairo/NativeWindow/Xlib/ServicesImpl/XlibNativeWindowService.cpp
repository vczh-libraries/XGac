#include "XlibNativeWindowService.h"
#include "../XlibNativeController.h"

#include <unistd.h>

using namespace vl::presentation;
using namespace vl::collections;

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

				XlibCairoWindow* XlibNativeWindowService::FindWindow(Window win)
				{
					if(win == XLIB_NONE)
						return dynamic_cast<XlibCairoWindow*>(GetMainWindow());
					FOREACH(XlibCairoWindow*, i, windows)
					{
						if(i->GetWindow() == win)
						{
							return i;
						}
					}

					return NULL;
				}

				void XlibNativeWindowService::Run(INativeWindow *window)
				{
					XEvent event;
					XlibCairoWindow* actualWindow = dynamic_cast<XlibCairoWindow*>(window);

					if(!window)
					{
						throw Exception(L"Invalid Window Type");
					}
					while(true)
					{
						while(XPending(actualWindow->GetDisplay()))
						{
							XlibCairoWindow* evWindow = NULL;
							XNextEvent(actualWindow->GetDisplay(), &event);
							switch(event.type)
							{
								case ButtonPress:
									if((evWindow = FindWindow(event.xbutton.subwindow)) != NULL)
										evWindow->MouseDownEvent(
												event.xbutton.button == Button1 ? X11CAIRO_LBUTTON : X11CAIRO_RBUTTON,
												Point(event.xbutton.x, event.xbutton.y)
												);

									break;

								case ButtonRelease:
									if((evWindow = FindWindow(event.xbutton.subwindow)) != NULL)
										evWindow->MouseUpEvent(
												event.xbutton.button == Button1 ? X11CAIRO_LBUTTON : X11CAIRO_RBUTTON,
												Point(event.xbutton.x, event.xbutton.y)
												);
									break;

								case MotionNotify:
									if((evWindow = FindWindow(event.xmotion.subwindow)) != NULL)
										evWindow->MouseMoveEvent( 
												Point(event.xmotion.x, event.xmotion.y)
												);
									break;

								case EnterNotify:
									if((evWindow = FindWindow(event.xcrossing.subwindow)) != NULL)
										evWindow->MouseEnterEvent();
									break;

								case LeaveNotify:
									if((evWindow = FindWindow(event.xcrossing.subwindow)) != NULL)
										evWindow->MouseEnterEvent();
									break;

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
