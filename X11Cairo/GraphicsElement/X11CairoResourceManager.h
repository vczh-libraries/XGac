#ifndef __X11_CAIRO_RESOURCE_MANAGER_H
#define __X11_CAIRO_RESOURCE_MANAGER_H

#include <GacUI.h>
namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			class IX11CairoResourceManager: public Interface
			{
			};

			extern void RegisterX11CairoResrouceManager();
		}
	}
}

#endif

