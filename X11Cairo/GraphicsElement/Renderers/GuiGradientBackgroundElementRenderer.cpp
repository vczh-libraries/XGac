#include "GuiGradientBackgroundElementRenderer.h"
#include "CairoHelpers.h"

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
				cairo_save(cairoContext);
				helpers::PathGenerate(cairoContext, element->GetShape(), bounds);
				helpers::GradientFill(cairoContext,
						element->GetColor1(),
						element->GetColor2(),
						bounds,
						helpers::ConvertDirection(element->GetDirection()),
						false);
				cairo_restore(cairoContext);
			}

			void GuiGradientBackgroundElementRenderer::OnElementStateChanged()
			{
			}

			void GuiGradientBackgroundElementRenderer::RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT)
			{
				if(newRT)
					cairoContext = newRT->GetCairoContext();
				else cairoContext = NULL;
			}
		}
	}
}
