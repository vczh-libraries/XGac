#ifndef __GAC_X11CAIRO_GUI_GRADIENT_BACKGROUND_ELEMENT_RENDERER_H
#define __GAC_X11CAIRO_GUI_GRADIENT_BACKGROUND_ELEMENT_RENDERER_H

#include <GacUI.h>
#include "../X11CairoRenderTarget.h"

namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			using namespace elements;
			class GuiGradientBackgroundElementRenderer: public Object, public IGuiGraphicsRenderer
			{
				DEFINE_GUI_GRAPHICS_RENDERER(GuiGradientBackgroundElement, GuiGradientBackgroundElementRenderer, IX11CairoRenderTarget);

			protected:
				cairo_t* cairoContext;

			public:
				GuiGradientBackgroundElementRenderer();

				void InitializeInternal();
				void FinalizeInternal();
				void Render(Rect bounds);
				void OnElementStateChanged();
				void RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT);
			};
		}
	}
}


#endif


