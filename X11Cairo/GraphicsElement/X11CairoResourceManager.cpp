#include "X11CairoResourceManager.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			class X11CairoResourceManager: public elements::GuiGraphicsResourceManager, public IX11CairoResourceManager
			{
			};
		}
	}
}
