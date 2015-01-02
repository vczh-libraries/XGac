#ifndef __GAC_X11_CAIRO_WINDOW_H
#define __GAC_X11_CAIRO_WINDOW_H

#include <GacUI.h>

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			class IX11CairoWindow: public INativeWindow, public Description<IX11CairoWindow> 
			{
			public:
				virtual void SetRenderTarget(elements::IGuiGraphicsRenderTarget*) = 0;

				virtual elements::IGuiGraphicsRenderTarget* GetRenderTarget() = 0;
			};
		}
	}
}

#endif
