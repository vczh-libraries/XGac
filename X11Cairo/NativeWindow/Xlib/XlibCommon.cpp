#include "XlibCommon.h"
#include <X11/extensions/record.h>

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				bool CheckXdbeExtension(Display* display)
				{
					int major, minor;
					if(XdbeQueryExtension(display, &major, &minor))
					{
						if(major >= 1)
							return true;
					}

					return false;
				}

				bool CheckXRecordExtension(Display* display)
				{
					int major, minor;
					if(XRecordQueryVersion(display, &major, &minor))
					{
						if(major >= 1)
							return true;
					}
					return false;
				}
			}
		}
	}
}


