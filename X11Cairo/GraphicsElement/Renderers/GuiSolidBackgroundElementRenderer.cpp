#include "GuiSolidBackgroundElementRenderer.h"


namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			GuiSolidBackgroundElementRenderer::GuiSolidBackgroundElementRenderer()
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
			}

			void GuiSolidBackgroundElementRenderer::OnElementStateChanged()
			{
			}

			void GuiSolidBackgroundElementRenderer::RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT)
			{
			}
		}
	}
}
