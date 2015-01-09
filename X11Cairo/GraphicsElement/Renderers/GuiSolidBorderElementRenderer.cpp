#include "GuiSolidBorderElementRenderer.h"
#include "CairoHelpers.h"


namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			GuiSolidBorderElementRenderer::GuiSolidBorderElementRenderer():
				minSize(1, 1), cairoContext(NULL)
			{
			}


			void GuiSolidBorderElementRenderer::InitializeInternal()
			{
			}

			void GuiSolidBorderElementRenderer::FinalizeInternal()
			{
			}

			void GuiSolidBorderElementRenderer::Render(Rect bounds)
			{
				Color color = element->GetColor();
				cairo_save(cairoContext);
				cairo_set_source_rgb(cairoContext, 1.0 * color.r / 255, 1.0 * color.g / 255, 1.0 * color.b / 255);

				cairo_set_line_width(cairoContext, 1.0);
				helpers::PathGenerate(cairoContext, element->GetShape(), bounds);
				helpers::PathStroke(cairoContext, color);
			}

			void GuiSolidBorderElementRenderer::OnElementStateChanged()
			{
			}

			void GuiSolidBorderElementRenderer::RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT)
			{
				if(cairoContext)
					cairo_destroy(cairoContext);
				if(newRT) cairoContext = cairo_create(newRT->GetCairoSurface());
			}
		}
	}
}
