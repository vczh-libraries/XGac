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
					recordHelper = new XlibXRecordMouseHookHelper(XDisplayString(display));
				}

				XlibNativeWindowService::~XlibNativeWindowService()
				{
					delete recordHelper;
				}

				INativeWindow *XlibNativeWindowService::CreateNativeWindow()
				{
					XlibWindow *window = new XlibWindow(display);
					windows.Add(window);

					return window;
				}

				void XlibNativeWindowService::DestroyNativeWindow(INativeWindow *window)
				{
					if (window)
					{
						XlibWindow* actualWindow = dynamic_cast<XlibWindow*>(window);
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

				XlibWindow* XlibNativeWindowService::FindWindow(Window win)
				{
					if(win == XLIB_NONE)
						return dynamic_cast<XlibWindow*>(GetMainWindow());
					FOREACH(XlibWindow*, i, windows)
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
					XlibWindow* actualWindow = dynamic_cast<XlibWindow*>(window);

					if(!window)
					{
						throw Exception(L"Invalid Window Type");
					}

					recordHelper->StartCapture();

					while(true)
					{
	
						recordHelper->Update();

						recordHelper->ProcessEvents(
								[this](MouseEvent ev)
								{
									switch(ev.type)
									{
									case MouseEventType::BUTTONDOWN:
										callbackService->MouseDownEvent(ev.button, ev.position);
										break;
									case MouseEventType::BUTTONUP:
										callbackService->MouseUpEvent(ev.button, ev.position);
										break;
									case MouseEventType::POINTERMOVE:
										callbackService->MouseMoveEvent(ev.position);
										break;
									}
								});
								

						while(XPending(actualWindow->GetDisplay()))
						{
							XlibWindow* evWindow = NULL;
							XNextEvent(actualWindow->GetDisplay(), &event);
							switch(event.type)
							{
								case ButtonPress:
									if((evWindow = FindWindow(event.xbutton.window)) != NULL)
										evWindow->MouseDownEvent(
												event.xbutton.button == Button1 ? MouseButton::LBUTTON : MouseButton::RBUTTON,
												Point(event.xbutton.x, event.xbutton.y),
												event.xbutton.state & ControlMask,
												event.xbutton.state & ShiftMask
												);

									break;

								case ButtonRelease:
									if((evWindow = FindWindow(event.xbutton.window)) != NULL)
										evWindow->MouseUpEvent(
												event.xbutton.button == Button1 ? MouseButton::LBUTTON : MouseButton::RBUTTON,
												Point(event.xbutton.x, event.xbutton.y),
												event.xbutton.state & ControlMask,
												event.xbutton.state & ShiftMask
												);
									break;

								case MotionNotify:
									if((evWindow = FindWindow(event.xmotion.window)) != NULL)
										evWindow->MouseMoveEvent( 
												Point(event.xmotion.x, event.xmotion.y)
												);
									break;

								case EnterNotify:
									if((evWindow = FindWindow(event.xcrossing.window)) != NULL)
										evWindow->MouseEnterEvent();
									break;

								case LeaveNotify:
									if((evWindow = FindWindow(event.xcrossing.window)) != NULL)
										evWindow->MouseEnterEvent();
									break;

								case ClientMessage:
									// TODO: Handle different client messages
									goto Cleanup;

								case ConfigureNotify:
									if((evWindow = FindWindow(event.xconfigure.window)) != NULL)
										evWindow->ResizeEvent(event.xconfigure.width, event.xconfigure.height);
									break;

								default:
									break;
							}
						}

						asyncService->ExecuteAsyncTasks();
						callbackService->CheckTimer();
					
						XFlush(actualWindow->GetDisplay());

						pause();
					}

Cleanup:
					recordHelper->EndCapture();
					XFlush(actualWindow->GetDisplay());
					return;
				}
			}
		}
	}
}
