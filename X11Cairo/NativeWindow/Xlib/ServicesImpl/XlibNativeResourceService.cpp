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
					FontProperties prop;
					{
						prop.fontFamily = L"Sans";
						prop.size = 12;
						prop.italic = false;
						prop.bold = false;
						prop.underline = false;
						prop.strikeline = false;
						prop.antialias = true;
						prop.verticalAntialias = true;
					}
					return prop;
				}

				void XlibNativeResourceService::SetDefaultFont(const FontProperties& value)
				{
					//TODO
				}
			}
		}
	}
}
