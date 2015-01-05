#include "GuiGradientBackgroundElementRenderer.h"

namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			GuiGradientBackgroundElementRenderer::GuiGradientBackgroundElementRenderer():
				minSize(1, 1), cairoContext(NULL)
			{
			}


			void GuiGradientBackgroundElementRenderer::InitializeInternal()
			{
				if(element) OnElementStateChanged();
			}

			void GuiGradientBackgroundElementRenderer::FinalizeInternal()
			{
			}

			void GuiGradientBackgroundElementRenderer::Render(Rect bounds)
			{
				cairo_pattern_t* pattern = NULL;
				Color color1 = element->GetColor1();
				Color color2 = element->GetColor2();

				int midX = bounds.x1 + bounds.Width() / 2;
				int midY = bounds.y1 + bounds.Height() / 2;

				switch(element->GetDirection())
				{
					case GuiGradientBackgroundElement::Horizontal:
						pattern = cairo_pattern_create_linear(bounds.x1, midY, bounds.x2, midY);
						break;
					case GuiGradientBackgroundElement::Vertical:
						pattern = cairo_pattern_create_linear(midX, bounds.y1, midX, bounds.y2);
						break;
					case GuiGradientBackgroundElement::Slash:
						pattern = cairo_pattern_create_linear(bounds.x1, bounds.y2, bounds.x2, bounds.y1);
						break;
					case GuiGradientBackgroundElement::Backslash:
						pattern = cairo_pattern_create_linear(bounds.x1, bounds.x2, bounds.y1, bounds.y2);
						break;
					default:
						throw Exception(L"Illegal gradient direction");
				}

				cairo_pattern_add_color_stop_rgb(pattern, 0, 1.0 * color1.r / 255, 1.0 * color1.g / 255, 1.0 * color1.b / 255);
				cairo_pattern_add_color_stop_rgb(pattern, 1, 1.0 * color2.r / 255, 1.0 * color2.g / 255, 1.0 * color2.b / 255);

				cairo_pattern_add_color_stop_rgb(pattern, 0.49, 1.0 * color1.r / 255, 1.0 * color1.g / 255, 1.0 * color1.b / 255);
				cairo_pattern_add_color_stop_rgb(pattern, 0.51, 1.0 * color2.r / 255, 1.0 * color2.g / 255, 1.0 * color2.b / 255);
				cairo_set_source(cairoContext, pattern);

				cairo_rectangle(cairoContext, bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
				cairo_fill(cairoContext);

				cairo_pattern_destroy(pattern);
			}

			void GuiGradientBackgroundElementRenderer::OnElementStateChanged()
			{
			}

			void GuiGradientBackgroundElementRenderer::RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT)
			{
				if(cairoContext)
					cairo_destroy(cairoContext);
				if(newRT) cairoContext = cairo_create(newRT->GetCairoSurface());
			}
		}
	}
}
