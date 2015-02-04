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
					callbackService(callbackService),
					mainWindow(NULL)
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
					// Find the top-most window
					Window seekWindow = XDefaultRootWindow(display);
					Window resultWindow = seekWindow;
					int x = 0, y = 0;

					while(true)
					{
						if(XTranslateCoordinates(display, XDefaultRootWindow(display), seekWindow,
							   location.x, location.y, &x, &y, &resultWindow) == XLIB_TRUE)
						{
							if(resultWindow != XLIB_NONE)
							{
								seekWindow = resultWindow;
							}
							else
							{
								return FindWindow(seekWindow);
							}
						}
						else break;
					}

					return NULL;
				}

				XlibWindow* XlibNativeWindowService::FindWindow(Window win)
				{
					FOREACH(XlibWindow*, i, windows)
					{
						if(i->GetWindow() == win)
						{
							return i;
						}
					}

					return NULL;
				}


				NativeWindowMouseInfo XlibNativeWindowService::MouseStateMaskToInfo(int x, int y, unsigned int state)
				{
					NativeWindowMouseInfo result;
					{
						result.x = x;
						result.y = y;
						result.left = state & Button1Mask;
						result.right = state & Button2Mask;
						result.middle = state & Button3Mask;
						result.ctrl = state & ControlMask;
						result.shift = state & ShiftMask;
						result.wheel = 0; // TODO
						result.nonClient = false;
					}

					return result;
				}

				MouseButton XlibNativeWindowService::XButtonCodeToButton(unsigned int button)
				{
					switch(button)
					{
						default:
						case Button1:
							return MouseButton::LBUTTON;
						case Button2:
							return MouseButton::RBUTTON;
						case Button3:
							return MouseButton::MBUTTON;
					}
				}

				void XlibNativeWindowService::Run(INativeWindow *window)
				{
					XEvent event;
					mainWindow = dynamic_cast<XlibWindow*>(window);

					if(!mainWindow)
					{
						throw Exception(L"Invalid Window Type");
					}

					mainWindow->Show();
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
								

						while(XPending(mainWindow->GetDisplay()))
						{
							XlibWindow* evWindow = NULL;
							XNextEvent(mainWindow->GetDisplay(), &event);
							switch(event.type)
							{
								case ButtonPress:
									if((evWindow = FindWindow(event.xbutton.window)) != NULL)
										evWindow->MouseDownEvent(
													XButtonCodeToButton(event.xbutton.button),
													MouseStateMaskToInfo(event.xbutton.x, event.xbutton.y, event.xbutton.state)
												);

									break;

								case ButtonRelease:
									if((evWindow = FindWindow(event.xbutton.window)) != NULL)
										evWindow->MouseUpEvent(
													XButtonCodeToButton(event.xbutton.button),
													MouseStateMaskToInfo(event.xbutton.x, event.xbutton.y, event.xbutton.state)
												);
									break;

								case MotionNotify:
									if((evWindow = FindWindow(event.xmotion.window)) != NULL)
										evWindow->MouseMoveEvent( 
													MouseStateMaskToInfo(event.xmotion.x, event.xmotion.y, event.xbutton.state)
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

								case VisibilityNotify:
									if(event.xvisibility.state != VisibilityUnobscured)
									{
										FOREACH(XlibWindow*, i, windows)
										{
											i->VisibilityEvent(event.xvisibility.window);
										}
									}

								default:
									break;
							}
						}

						asyncService->ExecuteAsyncTasks();
						callbackService->CheckTimer();
					
						XFlush(mainWindow->GetDisplay());

						pause();
					}

Cleanup:
					recordHelper->EndCapture();
					XFlush(mainWindow->GetDisplay());

					mainWindow = NULL;

					return;
				}
			}
		}
	}
}
