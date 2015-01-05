#include <math.h>
#include "GuiSolidBorderElementRenderer.h"


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
				cairo_set_source_rgb(cairoContext, 1.0 * color.r / 255, 1.0 * color.g / 255, 1.0 * color.b / 255);

				cairo_set_line_width(cairoContext, 1.0);
				if(element->GetShape() == ElementShape::Rectangle)
				{
					//Add 0.5 to make this line pass through the center of pixel
					cairo_rectangle(cairoContext, 0.5 + bounds.x1, 0.5 + bounds.y1, 0.5 + bounds.Width(),0.5 + bounds.Height());
					cairo_stroke(cairoContext);
				}
				else if(element->GetShape() == ElementShape::Rectangle)
				{
					cairo_save(cairoContext);
					cairo_translate(cairoContext, bounds.x1 + bounds.Width() / 2, bounds.y1 + bounds.Height());
					cairo_scale(cairoContext, bounds.Width() / 2, bounds.Height() / 2);
					cairo_arc(cairoContext, 0.0, 0.0, 1.0, 0.0, 2 * M_PI);
					cairo_set_line_width(cairoContext, 0.5);
					cairo_stroke(cairoContext);
					cairo_restore(cairoContext);
				}

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
