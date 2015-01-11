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

				//Actual left-top point of the shape
				int ptx = bounds.x1 + (bounds.Width() - element->GetSize().x) / 2;
				int pty = bounds.y1 + (bounds.Height() - element->GetSize().y) / 2;

				cairo_move_to(cairoContext, 0.5 + ptx + element->GetPoint(0).x, 0.5 + pty + element->GetPoint(0).y);
				for(int i = 1; i < element->GetPointCount(); i++)
				{
					cairo_line_to(cairoContext, 0.5 + ptx + element->GetPoint(i).x, 0.5 + pty + element->GetPoint(i).y);
				}
				cairo_close_path(cairoContext);

				helpers::ColorSet(cairoContext, bg);
				cairo_fill_preserve(cairoContext);

				helpers::PathStroke(cairoContext, border, 1.0);

				cairo_restore(cairoContext);

			}
		}
	}
}
