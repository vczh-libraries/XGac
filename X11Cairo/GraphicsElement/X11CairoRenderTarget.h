#ifndef __GAC_X11CAIRO_X11_CAIRO_RENDER_TARGET_H
#define __GAC_X11CAIRO_X11_CAIRO_RENDER_TARGET_H

#include <GacUI.h>
#include "CairoPangoIncludes.h"
#include "../NativeWindow/Common/X11CairoWindow.h"

namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			class IX11CairoRenderTarget: public elements::IGuiGraphicsRenderTarget
			{
			public:
				virtual cairo_surface_t* GetCairoSurface() = 0;
				virtual cairo_t* GetCairoContext() = 0;
			};

			extern IX11CairoRenderTarget* CreateX11CairoRenderTarget(x11cairo::IX11CairoWindow* window);
			extern void DestroyX11CairoRenderTarget(IX11CairoRenderTarget* target);
		}
	}
}



#endif
