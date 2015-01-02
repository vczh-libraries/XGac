#include "XlibNativeResourceService.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				INativeCursor* XlibNativeResourceService::GetSystemCursor(INativeCursor::SystemCursorType type)
				{
					//TODO
					return NULL;
				}

				INativeCursor* XlibNativeResourceService::GetDefaultSystemCursor()
				{
					//TODO
					return NULL;
				}

				FontProperties XlibNativeResourceService::GetDefaultFont()
				{
					//TODO
					return FontProperties();
				}

				void XlibNativeResourceService::SetDefaultFont(const FontProperties& value)
				{
					//TODO
				}
			}
		}
	}
}
