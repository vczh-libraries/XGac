#ifndef __GUI_GRAPHICS_X11_CAIRO_H
#define __GUI_GRAPHICS_X11_CAIRO_H

#include <GacUI.h>
#include "CairoPangoIncludes.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			class GuiX11CairoElement;

			struct GuiX11CairoElementEventArgs: compositions::GuiEventArgs
			{
			public:
				GuiX11CairoElement* element;

			};

			class GuiX11CairoElement: public Object, public IGuiGraphicsElement, public Description<GuiX11CairoElement>
			{
				DEFINE_GUI_GRAPHICS_ELEMENT(GuiX11CairoElement, L"X11CairoElement");

			protected:
				GuiX11CairoElement();

			public:
				~GuiCoreGraphicsElement();

			};
		}
		namespace elements_x11cairo
		{
			class IX11CairoRenderTarget: public elements::IGuiGraphicsRenderTarget
			{
			public:
				virtual cairo_surface_t* GetCairoSurface() = 0;
			};

		}
	}
}


#endif
