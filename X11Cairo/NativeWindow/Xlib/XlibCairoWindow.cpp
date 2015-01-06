#include <limits.h>
#include "XlibCairoWindow.h"

using namespace vl::collections;

namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
                XlibCairoWindow::XlibCairoWindow(Display *display):
                        display(display),
                        title(),
						renderTarget(nullptr),
						resizable (false),
						doubleBuffer(false),
						backBuffer(XLIB_NONE)
                {
                    this->display = display;
                    window = XCreateWindow(
							display,                 //Display
							XRootWindow(display, 0), //Root Display
							0,                       //X
						   	0,                       //Y
							400,                     //Width
							200,                     //Height
							2,                       //Border Width
							CopyFromParent,          //Depth
							InputOutput,             //Class
						   	CopyFromParent,          //Visual
							0,                       //Value Mask
							NULL                     //Attributes
							);

					Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", XLIB_FALSE);

					XSelectInput(display, window, PointerMotionMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask);
					XSetWMProtocols(display, window, &WM_DELETE_WINDOW, 1);

					CheckDoubleBuffer();

                    Show();
                    UpdateTitle();
                    XSync(display, false);
                }

                XlibCairoWindow::~XlibCairoWindow()
                {
                    XDestroyWindow(display, window);
                }

				void XlibCairoWindow::CheckDoubleBuffer()
				{
					int major, minor;
					if(XdbeQueryExtension(display, &major, &minor))
					{
						backBuffer = XdbeAllocateBackBufferName(display, window, XdbeUndefined);
						if(backBuffer != XLIB_NONE)
						{
							doubleBuffer = true;
						}
					}
				}

				XdbeBackBuffer XlibCairoWindow::GetBackBuffer()
				{
					return backBuffer;
				}

				bool XlibCairoWindow::GetDoubleBuffer()
				{
					return doubleBuffer;
				}

				void XlibCairoWindow::UpdateResizable()
				{
					XSizeHints *hints = XAllocSizeHints();
					Size currentSize = GetClientSize();
					XGetNormalHints(display, window, hints);
					if(resizable)
					{
						hints->min_width = currentSize.x;
						hints->min_height = currentSize.y;
						hints->max_width = currentSize.x;
						hints->max_height = currentSize.y;
					}
					else
					{
						hints->min_width = 0;
						hints->min_height = 0;
						hints->max_width = INT_MAX;
						hints->max_height = INT_MAX;
					}
					XSetNormalHints(display, window, hints);
					XFree(hints);
				}

                Window XlibCairoWindow::GetWindow()
                {
                    return window;
                }

                Display* XlibCairoWindow::GetDisplay()
                {
                    return display;
                }

				void XlibCairoWindow::SetRenderTarget(elements::IGuiGraphicsRenderTarget* target)
				{
					renderTarget = target;
				}

				elements::IGuiGraphicsRenderTarget* XlibCairoWindow::GetRenderTarget()
				{
					return renderTarget;
				}

                void XlibCairoWindow::UpdateTitle()
                {
                    AString narrow = wtoa(title);
                    XStoreName(display, window, narrow.Buffer());
                }

				void XlibCairoWindow::MouseUpEvent(MouseButtons button, Point position)
				{
					NativeWindowMouseInfo info;
					{
						info.x = position.x;
						info.y = position.y;
						info.left = (button == X11CAIRO_LBUTTON) ? true : false;
						info.right = (button == X11CAIRO_RBUTTON) ? true : false;
					}
					switch(button)
					{
						case X11CAIRO_LBUTTON:
							FOREACH(INativeWindowListener*, i, listeners)
							{
								i->LeftButtonUp(info);
							}
							break;

						case X11CAIRO_RBUTTON:
							FOREACH(INativeWindowListener*, i, listeners)
							{
								i->RightButtonUp(info);
							}
							break;
					}
				}

				void XlibCairoWindow::MouseDownEvent(MouseButtons button, Point position)
				{
					NativeWindowMouseInfo info;
					{
						info.x = position.x;
						info.y = position.y;
						info.left = (button == X11CAIRO_LBUTTON) ? true : false;
						info.right = (button == X11CAIRO_RBUTTON) ? true : false;
					}
					switch(button)
					{
						case X11CAIRO_LBUTTON:
							FOREACH(INativeWindowListener*, i, listeners)
							{
								i->LeftButtonDown(info);
							}
							break;

						case X11CAIRO_RBUTTON:
							FOREACH(INativeWindowListener*, i, listeners)
							{
								i->RightButtonDown(info);
							}
							break;
					}
				}

				void XlibCairoWindow::MouseMoveEvent(Point position)
				{
					NativeWindowMouseInfo info;
					{
						info.x = position.x;
						info.y = position.y;
					}

					FOREACH(INativeWindowListener*, i, listeners)
					{
						i->MouseMoving(info);
					}
				}
				
				void XlibCairoWindow::MouseEnterEvent()
				{
					FOREACH(INativeWindowListener*, i, listeners)
					{
						i->MouseEntered();
					}
				}

				void XlibCairoWindow::MouseLeaveEvent()
				{
					FOREACH(INativeWindowListener*, i, listeners)
					{
						i->MouseLeaved();
					}
				}

                void XlibCairoWindow::Show ()
                {
                    XMapWindow(display, window);
                }

                void XlibCairoWindow::Hide ()
                {
                    XUnmapWindow(display, window);
                }

                Rect XlibCairoWindow::GetBounds()
                {
                    //TODO
					XWindowAttributes attr;
					XGetWindowAttributes(display, window, &attr);
                    return Rect(attr.x, attr.y, attr.x + attr.width, attr.y + attr.height);
                }

                void XlibCairoWindow::SetBounds(const Rect &bounds)
                {
                    //TODO
					XMoveResizeWindow(display, window, bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
                }

                Size XlibCairoWindow::GetClientSize()
                {
					XWindowAttributes attr;
					XGetWindowAttributes(display, window, &attr);
					return Size(attr.width, attr.height);
                }

                void XlibCairoWindow::SetClientSize(Size size)
                {
					XResizeWindow(display, window, size.x, size.y);
                }

                Rect XlibCairoWindow::GetClientBoundsInScreen()
                {
                    //TODO
                    return Rect();
                }

                WString XlibCairoWindow::GetTitle()
                {
                    return title;
                }

                void XlibCairoWindow::SetTitle(WString title)
                {
                    this->title = title;
                    UpdateTitle();
                }

                INativeCursor *XlibCairoWindow::GetWindowCursor()
                {
                    //TODO
                    return NULL;
                }

                void XlibCairoWindow::SetWindowCursor(INativeCursor *cursor)
                {
                    //TODO
                }

                Point XlibCairoWindow::GetCaretPoint()
                {
                    //TODO
                    return Point();
                }

                void XlibCairoWindow::SetCaretPoint(Point point)
                {
                    //TODO
                }

                INativeWindow *XlibCairoWindow::GetParent()
                {
                    //TODO
                    return NULL;
                }

                void XlibCairoWindow::SetParent(INativeWindow *parent)
                {
                    //TODO
                }

                bool XlibCairoWindow::GetAlwaysPassFocusToParent()
                {
                    //TODO
                    return false;
                }

                void XlibCairoWindow::SetAlwaysPassFocusToParent(bool value)
                {
                    //TODO
                }

                void XlibCairoWindow::EnableCustomFrameMode()
                {
                    //TODO
                }

                void XlibCairoWindow::DisableCustomFrameMode()
                {
                    //TODO
                }

                bool XlibCairoWindow::IsCustomFrameModeEnabled()
                {
                    //TODO
                    return false;
                }

                XlibCairoWindow::WindowSizeState XlibCairoWindow::GetSizeState()
                {
                    //TODO
                    return XlibCairoWindow::WindowSizeState::Restored;
                }

                void XlibCairoWindow::ShowDeactivated()
                {
                    //TODO
                }

                void XlibCairoWindow::ShowRestored()
                {
                    //TODO
                }

                void XlibCairoWindow::ShowMaximized()
                {
                    //TODO
                }

                void XlibCairoWindow::ShowMinimized()
                {
                    //TODO
                }

                bool XlibCairoWindow::IsVisible()
                {
                    //TODO
                    return true;
                }

                void XlibCairoWindow::Enable()
                {
                    //TODO
                }

                void XlibCairoWindow::Disable()
                {
                    //TODO
                }

                bool XlibCairoWindow::IsEnabled()
                {
                    //TODO
                    return true;
                }

                void XlibCairoWindow::SetFocus()
                {
                    //TODO
                }

                bool XlibCairoWindow::IsFocused()
                {
                    //TODO
                    return true;
                }

                void XlibCairoWindow::SetActivate()
                {
                    //TODO
                }

                bool XlibCairoWindow::IsActivated()
                {
                    //TODO
                    return true;
                }

                void XlibCairoWindow::ShowInTaskBar()
                {
                    //TODO
                }

                void XlibCairoWindow::HideInTaskBar()
                {
                    //TODO
                }

                bool XlibCairoWindow::IsAppearedInTaskBar()
                {
                    //TODO
                    return true;
                }

                void XlibCairoWindow::EnableActivate()
                {
                    //TODO
                }

                void XlibCairoWindow::DisableActivate()
                {
                    //TODO
                }

                bool XlibCairoWindow::IsEnabledActivate()
                {
                    //TODO
                    return true;
                }

                bool XlibCairoWindow::RequireCapture()
                {
                    //TODO
                    return false;
                }

                bool XlibCairoWindow::ReleaseCapture()
                {
                    //TODO
                    return true;
                }

                bool XlibCairoWindow::IsCapturing()
                {
                    //TODO
                    return false;
                }

                bool XlibCairoWindow::GetMaximizedBox()
                {
                    //TODO
                    return false;
                }

                void XlibCairoWindow::SetMaximizedBox(bool visible)
                {
                    //TODO
                }

                bool XlibCairoWindow::GetMinimizedBox()
                {
                    //TODO
                    return false;
                }

                void XlibCairoWindow::SetMinimizedBox(bool visible)
                {
                    //TODO
                }

                bool XlibCairoWindow::GetBorder()
                {
                    //TODO
                    return true;
                }

                void XlibCairoWindow::SetBorder(bool visible)
                {
                    //TODO
                }

                bool XlibCairoWindow::GetSizeBox()
                {
                    return resizable;
                }

                void XlibCairoWindow::SetSizeBox(bool visible)
                {
					resizable = visible;
					UpdateResizable();
                }

                bool XlibCairoWindow::GetIconVisible()
                {
                    //TODO
                    return true;
                }

                void XlibCairoWindow::SetIconVisible(bool visible)
                {
                    //TODO
                }

                bool XlibCairoWindow::GetTitleBar()
                {
                    //TODO
                    return true;
                }

                void XlibCairoWindow::SetTitleBar(bool visible)
                {
                    //TODO
                }

                bool XlibCairoWindow::GetTopMost()
                {
                    //TODO
                    return false;
                }

                void XlibCairoWindow::SetTopMost(bool topmost)
                {
                    //TODO
                }

                void XlibCairoWindow::SupressAlt()
                {
                    //TODO
                }

                bool XlibCairoWindow::InstallListener(INativeWindowListener *listener)
                {
					listeners.Add(listener);
					return true;
                }

                bool XlibCairoWindow::UninstallListener(INativeWindowListener *listener)
                {
					return listeners.Remove(listener);
                }

                void XlibCairoWindow::RedrawContent()
                {
                    //TODO
                }
            }
        }
    }
}

