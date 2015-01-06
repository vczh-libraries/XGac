#include "X11CairoRenderTarget.h"
#include "X11CairoResourceManager.h"


using namespace vl::presentation::x11cairo;
using namespace vl::presentation::elements;
using namespace vl::presentation::elements_x11cairo;

#ifndef GAC_CAIRO_XCB
#include "../NativeWindow/Xlib/XlibCairoWindow.h"
using namespace vl::presentation::x11cairo::xlib;
#endif

namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{

#ifndef GAC_CAIRO_XCB
			class X11CairoXlibRenderTarget: public IX11CairoRenderTarget, INativeWindowListener
			{
			private:
				cairo_surface_t* surface;
				XlibCairoWindow* window;

			public:
				X11CairoXlibRenderTarget(XlibCairoWindow* window):
					window(window)
				{
					Size size = window->GetClientSize();
					if(window->GetDoubleBuffer())
					{
						surface = cairo_xlib_surface_create(window->GetDisplay(), window->GetBackBuffer(), DefaultVisual(window->GetDisplay(), 0), size.x, size.y);
					}
					else
					{
						surface = cairo_xlib_surface_create(window->GetDisplay(), window->GetWindow(), DefaultVisual(window->GetDisplay(), 0), size.x, size.y);
					}

					if(!surface)
						throw Exception(L"Failed to create Cairo Surface");

					window->InstallListener(this);

				}

				virtual ~X11CairoXlibRenderTarget()
				{
					window->UninstallListener(this);
					cairo_surface_destroy(surface);
				}

				cairo_surface_t* GetCairoSurface()
				{
					return surface;
				}

				void StartRendering()
				{
				}

				bool StopRendering()
				{
					if(window->GetDoubleBuffer())
					{
						window->SwapBuffer();
					}

					return true;
				}

				void PushClipper(Rect clipper)
				{
					//TODO
				}

				void PopClipper()
				{
					//TODO
				}

				Rect GetClipper()
				{
					//TODO
					return Rect();
				}

				bool IsClipperCoverWholeTarget()
				{
					//TODO
					return false;
				}


				void Moving(Rect& bounds, bool fixSizeOnly) 
				{ 
					Size size = window->GetClientSize();
					if(window->GetDoubleBuffer())
					{
						cairo_xlib_surface_set_drawable(surface, window->GetBackBuffer(), size.x, size.y);
					}
					else
					{
						cairo_xlib_surface_set_size(surface, size.x, size.y);
					}
				}

				HitTestResult		HitTest(Point location) { return BorderNoSizing; }
				void				Moved() { }
				void				Enabled() { }
				void				Disabled() { }
				void				GotFocus() { }
				void				LostFocus() { }
				void				Activated() { }
				void				Deactivated() { }
				void				Opened() { }
				void				Closing(bool& cancel) { }
				void				Closed() { }
				void				Paint() { }
				void				Destroying() { }
				void				Destroyed() { }

				void				LeftButtonDown(const NativeWindowMouseInfo& info) { }
				void				LeftButtonUp(const NativeWindowMouseInfo& info) { }
				void				LeftButtonDoubleClick(const NativeWindowMouseInfo& info) { }
				void				RightButtonDown(const NativeWindowMouseInfo& info) { }
				void				RightButtonUp(const NativeWindowMouseInfo& info) { }
				void				RightButtonDoubleClick(const NativeWindowMouseInfo& info) { }
				void				MiddleButtonDown(const NativeWindowMouseInfo& info) { }
				void				MiddleButtonUp(const NativeWindowMouseInfo& info) { }
				void				MiddleButtonDoubleClick(const NativeWindowMouseInfo& info) { }
				void				HorizontalWheel(const NativeWindowMouseInfo& info) { }
				void				VerticalWheel(const NativeWindowMouseInfo& info) { }
				void				MouseMoving(const NativeWindowMouseInfo& info) { }
				void				MouseEntered() { }
				void				MouseLeaved() { }

				void				KeyDown(const NativeWindowKeyInfo& info) { }
				void				KeyUp(const NativeWindowKeyInfo& info) { }
				void				SysKeyDown(const NativeWindowKeyInfo& info) { }
				void				SysKeyUp(const NativeWindowKeyInfo& info) { }
				void				Char(const NativeWindowCharInfo& info) { }


			};

			IX11CairoRenderTarget* CreateX11CairoRenderTarget(IX11CairoWindow* window)
			{
				XlibCairoWindow* xlibWindow = dynamic_cast<XlibCairoWindow*>(window);
				if(!xlibWindow)
					throw Exception(L"Invalid window");

				return new X11CairoXlibRenderTarget(xlibWindow);
			}
#else
#endif
			void DestroyX11CairoRenderTarget(IX11CairoRenderTarget* target)
			{
				delete target;
			}
		}
	}
}


