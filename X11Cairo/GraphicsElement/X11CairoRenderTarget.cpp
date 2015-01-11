#include <vector>

#include "X11CairoRenderTarget.h"
#include "X11CairoResourceManager.h"


using namespace vl::presentation::x11cairo;
using namespace vl::presentation::elements;
using namespace vl::presentation::elements_x11cairo;

#ifndef GAC_X11_XCB
#include "../NativeWindow/Xlib/XlibCairoWindow.h"
using namespace vl::presentation::x11cairo::xlib;
#endif

namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{

#ifndef GAC_X11_XCB
			class X11CairoXlibRenderTarget: public IX11CairoRenderTarget, INativeWindowListener
			{
			private:
				cairo_surface_t* surface;
				cairo_t* context;
				XlibCairoWindow* window;
				std::vector<Rect> clippers;


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

					context = cairo_create(surface);

					if(!surface || !context)
						throw Exception(L"Failed to create Cairo Surface / Context");

					window->InstallListener(this);

				}

				virtual ~X11CairoXlibRenderTarget()
				{
					window->UninstallListener(this);

					cairo_destroy(context);
					cairo_surface_destroy(surface);
				}

				cairo_surface_t* GetCairoSurface()
				{
					return surface;
				}

				cairo_t* GetCairoContext()
				{
					return context;
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
					cairo_save(context);

					if(clippers.size() != 0)
					{
						Rect previousClipper=GetClipper();

						clipper.x1=(previousClipper.x1>clipper.x1?previousClipper.x1:clipper.x1);
						clipper.y1=(previousClipper.y1>clipper.y1?previousClipper.y1:clipper.y1);
						clipper.x2=(previousClipper.x2<clipper.x2?previousClipper.x2:clipper.x2);
						clipper.y2=(previousClipper.y2<clipper.y2?previousClipper.y2:clipper.y2);
					}

					clippers.push_back(clipper);
					cairo_rectangle(context, clipper.x1, clipper.y1, clipper.Width(), clipper.Height());
					cairo_reset_clip(context);
					cairo_clip(context);
				}

				void PopClipper()
				{
					clippers.pop_back();
					cairo_restore(context);
				}

				Rect GetClipper()
				{
					return clippers.back();
				}

				bool IsClipperCoverWholeTarget()
				{
					double x1, x2, y1, y2;
					Size size = window->GetClientSize();
					Rect boundsWin(0, 0, size.x, size.y);
					cairo_clip_extents(context, &x1, &y1, &x2, &y2);
					Rect boundsClip(x1, x2, y1, y2);

					return (boundsWin == boundsClip);
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


