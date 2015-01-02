#include "XlibCairoWindow.h"

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
						renderTarget(nullptr)
                {
                    this->display = display;
                    window = XCreateWindow(display, XRootWindow(display, 0), 0, 0, 200, 200, CopyFromParent, InputOutput, CopyFromParent, CopyFromParent, 0, NULL);
                    Show();
                    UpdateTitle();
                    XSync(display, false);
                }

                XlibCairoWindow::~XlibCairoWindow()
                {
                    XDestroyWindow(display, window);
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
                    return Rect();
                }

                void XlibCairoWindow::SetBounds(const Rect &bounds)
                {
                    //TODO
                }

                Size XlibCairoWindow::GetClientSize()
                {
                    //TODO
                    return Size();
                }

                void XlibCairoWindow::SetClientSize(Size size)
                {
                    //TODO
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
                    //TODO
                    return true;
                }

                void XlibCairoWindow::SetSizeBox(bool visible)
                {
                    //TODO
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
                    //TODO
                    return false;
                }

                bool XlibCairoWindow::UninstallListener(INativeWindowListener *listener)
                {
                    //TODO
                    return false;
                }

                void XlibCairoWindow::RedrawContent()
                {
                    //TODO
                }
            }
        }
    }
}

