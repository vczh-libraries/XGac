#ifndef __GAC_X11CAIRO_XLIB_COMMON_H
#define __GAC_X11CAIRO_XLIB_COMMON_H

#include <GacUI.h>
#include "XlibIncludes.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				enum class MouseButton
				{
					LBUTTON,
					RBUTTON
				};

				enum class MouseEventType
				{
					BUTTONDOWN,
					BUTTONUP,
					POINTERMOVE
				};

				struct MouseEvent
				{
					MouseButton button;
					MouseEventType type;
					vl::presentation::Point position;

					MouseEvent(MouseButton button, MouseEventType type, int rootX, int rootY)
						: button(button), type(type), position(rootX, rootY) 
					{
					}

					MouseEvent()
					{
					}
				};

				bool CheckXdbeExtension(Display*);
				bool CheckXRecordExtension(Display*);
			}
		}
	}
}

#endif
