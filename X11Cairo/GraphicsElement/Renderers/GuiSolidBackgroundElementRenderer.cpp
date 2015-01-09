#include "GuiSolidBackgroundElementRenderer.h"
#include "CairoHelpers.h"


namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			GuiSolidBackgroundElementRenderer::GuiSolidBackgroundElementRenderer():
				minSize(1, 1), cairoContext(NULL)
			{
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

				cairo_save(cairoContext);
				helpers::PathGenerate(cairoContext, element->GetShape(), bounds);
				helpers::SolidFill(cairoContext, color);
				cairo_restore(cairoContext);
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
