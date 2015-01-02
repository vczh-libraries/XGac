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
			class X11CairoXlibRenderTarget: public IX11CairoRenderTarget
			{
			private:
				cairo_surface_t* surface;
				XlibCairoWindow* window;

			public:
				X11CairoXlibRenderTarget(XlibCairoWindow* window):
					window(window)
				{
					Size size = window->GetClientSize();
					surface = cairo_xlib_surface_create(window->GetDisplay(), window->GetWindow(), DefaultVisual(window->GetDisplay(), 0), size.x, size.y);
					if(!surface)
						throw Exception(L"Failed to create Cairo Surface");

				}

				virtual ~X11CairoXlibRenderTarget()
				{
					cairo_surface_destroy(surface);
				}

				cairo_surface_t* GetCairoSurface()
				{
					return surface;
				}

				void StartRendering()
				{
					if(window)
					{
						Size size = window->GetClientSize();
						cairo_xlib_surface_set_size(surface, size.x, size.y);
					}
				}

				bool StopRendering()
				{
					//TODO
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


