#include "GuiSolidBackgroundElementRenderer.h"


namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			GuiSolidBackgroundElementRenderer::GuiSolidBackgroundElementRenderer():
				cairoContext(nullptr)
			{
				minSize = Size(1, 1);
			}


			void GuiSolidBackgroundElementRenderer::InitializeInternal()
			{
			}

			void GuiSolidBackgroundElementRenderer::FinalizeInternal()
			{
			}

			void GuiSolidBackgroundElementRenderer::Render(Rect bounds)
			{
				Color color = element->GetColor();

				cairo_set_source_rgb(cairoContext, 1.0 * color.r / 255, 1.0 * color.g / 255, 1.0 * color.b / 255);
				cairo_rectangle(cairoContext, bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
				cairo_fill(cairoContext);
			}

			void GuiSolidBackgroundElementRenderer::OnElementStateChanged()
			{
			}

			void GuiSolidBackgroundElementRenderer::RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT)
			{
				if(cairoContext)
					cairo_destroy(cairoContext);
				if(newRT) cairoContext = cairo_create(newRT->GetCairoSurface());
			}
		}
	}
}
