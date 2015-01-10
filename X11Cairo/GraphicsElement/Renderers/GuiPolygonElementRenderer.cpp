#include "GuiPolygonElementRenderer.h"
#include "CairoHelpers.h"


namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			GuiPolygonElementRenderer::GuiPolygonElementRenderer()
			{
			}
			void GuiPolygonElementRenderer::InitializeInternal()
			{
			}

			void GuiPolygonElementRenderer::FinalizeInternal()
			{
			}

			void GuiPolygonElementRenderer::RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT)
			{
				if(newRT)
				{
					cairoContext = newRT->GetCairoContext();
					OnElementStateChanged();
				}
			}

			void GuiPolygonElementRenderer::OnElementStateChanged()
			{
			}

			void GuiPolygonElementRenderer::Render(Rect bounds)
			{
				cairo_save(cairoContext);

				Color bg = element->GetBackgroundColor();
				Color border = element->GetBorderColor();

				cairo_move_to(cairoContext, element->GetPoint(0).x + 0.5, element->GetPoint(0).y + 0.5);
				for(int i = 1; i < element->GetPointCount(); i++)
				{
					cairo_move_to(cairoContext, element->GetPoint(i).x + 0.5, element->GetPoint(i).y + 0.5);
				}
				cairo_close_path(cairoContext);

				helpers::ColorSet(cairoContext, bg);
				//cairo_fill_preserve(cairoContext);

				helpers::PathStroke(cairoContext, border, 1.0);

				cairo_restore(cairoContext);

			}
		}
	}
}
