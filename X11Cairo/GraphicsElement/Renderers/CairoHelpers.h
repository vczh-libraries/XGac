#ifndef GAC_X11CAIRO_CAIRO_HELPER_FUNCTIONS_H
#define GAC_X11CAIRO_CAIRO_HELPER_FUNCTIONS_H

#include <GacUI.h>
#include "../CairoPangoIncludes.h"

namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			using namespace elements;
			namespace helpers
			{
				enum class GradientDirection
				{
					Horizontal,
					Vertical,
					Slash,
					Backslash,
				};

				GradientDirection ConvertDirection(GuiGradientBackgroundElement::Direction direction);

				void PathGenerate(cairo_t* cairoContext, ElementShape shape, Rect bounds);

				void PathStroke(cairo_t* cairoContext, Color color, double thickness = 1.0);

				void SolidFill(cairo_t* cairoContext, Color color);

				void GradientFill(cairo_t* cairoContext, Color color1, Color color2, Rect bounds, GradientDirection direction, bool smooth = false);

				WString WebdingsMap(WString oldString);
			}
		}
	}
}

#endif
