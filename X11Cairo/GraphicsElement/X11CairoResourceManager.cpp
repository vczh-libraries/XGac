#include "X11CairoRenderTarget.h"
#include "X11CairoResourceManager.h"
#include "../NativeWindow/Common/X11CairoWindow.h"

using namespace vl::presentation::elements;
using namespace vl::presentation::elements_x11cairo;

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			class X11CairoResourceManager: public elements::GuiGraphicsResourceManager, public IX11CairoResourceManager
			{
				IGuiGraphicsRenderTarget* GetRenderTarget(INativeWindow* window)
				{
					IX11CairoWindow* xWindow = dynamic_cast<IX11CairoWindow*>(window);
					if(!xWindow) throw Exception(L"Invalid Window");

					IX11CairoRenderTarget* renderTarget = dynamic_cast<IX11CairoRenderTarget*>(xWindow->GetRenderTarget());
					if(!renderTarget)
					{
						RecreateRenderTarget(window);
						renderTarget = dynamic_cast<IX11CairoRenderTarget*>(xWindow->GetRenderTarget());
					}

					if(xWindow->GetClientSize() != renderTarget->GetSize())
						renderTarget->Resize(xWindow->GetClientSize());

					return renderTarget;
				}
				void RecreateRenderTarget(INativeWindow* window)
				{
					IX11CairoWindow* xWindow = dynamic_cast<IX11CairoWindow*>(window);
					if(!xWindow) throw Exception(L"Invalid Window");

					if(xWindow->GetRenderTarget()) delete xWindow->GetRenderTarget();

					xWindow->SetRenderTarget(CreateX11CairoRenderTarget(xWindow));
				}
				IGuiGraphicsLayoutProvider* GetLayoutProvider()
				{
					//TODO
					return NULL;
				}
			};

			void RegisterX11CairoResourceManager()
			{
				SetGuiGraphicsResourceManager(new X11CairoResourceManager());
			}
		}
	}
}

