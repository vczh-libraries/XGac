#ifndef __GAC_X11CAIRO_GUI_GRAPHICS_X11_CAIRO_H
#define __GAC_X11CAIRO_GUI_GRAPHICS_X11_CAIRO_H

#include <GacUI.h>
#include "CairoPangoIncludes.h"

namespace vl
{
	namespace presentation
	{
		namespace elements
		{
			class GuiX11CairoElement;

			struct GuiX11CairoElementEventArgs: compositions::GuiEventArgs
			{
			public:
				GuiX11CairoElement* element;

			};

			class GuiX11CairoElement: public Object, public elements::IGuiGraphicsElement, public Description<GuiX11CairoElement>
			{
				DEFINE_GUI_GRAPHICS_ELEMENT(GuiX11CairoElement, L"X11CairoElement");

			protected:
				GuiX11CairoElement();

			public:
				~GuiX11CairoElement();
			};
		}
	}
}


#endif
