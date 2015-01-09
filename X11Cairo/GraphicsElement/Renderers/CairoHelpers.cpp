#include <math.h>
#include "CairoHelpers.h"

namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			namespace helpers
			{
				GradientDirection ConvertDirection(GuiGradientBackgroundElement::Direction direction)
				{
					switch(direction)
					{
						case GuiGradientBackgroundElement::Horizontal:
							return GradientDirection::Horizontal;
						case GuiGradientBackgroundElement::Vertical:
							return GradientDirection::Vertical;
						case GuiGradientBackgroundElement::Slash:
							return GradientDirection::Slash;
						case GuiGradientBackgroundElement::Backslash:
							return GradientDirection::Backslash;
					}

					return GradientDirection();
				}

				void PathGenerate(cairo_t* cairoContext, ElementShape shape, Rect bounds)
				{
					switch(shape)
					{
						case ElementShape::Rectangle:
							//Add 0.5 to make this line pass through the center of pixel
							cairo_rectangle(cairoContext, 0.5 + bounds.x1, 0.5 + bounds.y1, - 1.0 + bounds.Width(), - 1.0 + bounds.Height());
							break;
						case ElementShape::Ellipse:
							cairo_translate(cairoContext, bounds.x1 + bounds.Width() / 2 + 0.5, bounds.y1 + bounds.Height() / 2 + 0.5);
							cairo_scale(cairoContext, bounds.Width() / 2 - 0.5, bounds.Height() / 2 - 0.5);
							cairo_arc(cairoContext, 0.0, 0.0, 1.0, 0.0, 2 * M_PI);
							cairo_identity_matrix(cairoContext);
							break;
					}
				}

				void SolidFill(cairo_t* cairoContext, Color color)
				{
					cairo_set_source_rgba(cairoContext, 1.0 * color.r / 255, 1.0 * color.g / 255, 1.0 * color.b / 255, 1.0 * color.a / 255);
					cairo_fill(cairoContext);
				}

				void GradientFill(cairo_t* cairoContext, Color color1, Color color2, Rect bounds, GradientDirection direction, bool smooth)
				{
					cairo_pattern_t* pattern = NULL;

					int midX = bounds.x1 + bounds.Width() / 2;
					int midY = bounds.y1 + bounds.Height() / 2;

					switch(direction)
					{
						case GradientDirection::Horizontal:
							pattern = cairo_pattern_create_linear(bounds.x1, midY, bounds.x2, midY);
							break;
						case GradientDirection::Vertical:
							pattern = cairo_pattern_create_linear(midX, bounds.y1, midX, bounds.y2);
							break;
						case GradientDirection::Slash:
							pattern = cairo_pattern_create_linear(bounds.x1, bounds.y2, bounds.x2, bounds.y1);
							break;
						case GradientDirection::Backslash:
							pattern = cairo_pattern_create_linear(bounds.x1, bounds.x2, bounds.y1, bounds.y2);
							break;
						default:
							throw Exception(L"Illegal gradient direction");
					}

					cairo_pattern_add_color_stop_rgba(pattern, 0, 1.0 * color1.r / 255, 1.0 * color1.g / 255, 1.0 * color1.b / 255, 1.0 * color1.a / 255);
					cairo_pattern_add_color_stop_rgba(pattern, 1, 1.0 * color2.r / 255, 1.0 * color2.g / 255, 1.0 * color2.b / 255, 1.0 * color2.a / 255);

					if(!smooth)
					{
						cairo_pattern_add_color_stop_rgba(pattern, 0.49, 1.0 * color1.r / 255, 1.0 * color1.g / 255, 1.0 * color1.b / 255, 1.0 * color1.a / 255);
						cairo_pattern_add_color_stop_rgba(pattern, 0.51, 1.0 * color2.r / 255, 1.0 * color2.g / 255, 1.0 * color2.b / 255, 1.0 * color2.a / 255);
					}
					cairo_set_source(cairoContext, pattern);

					cairo_fill(cairoContext);

					cairo_pattern_destroy(pattern);
				}


				void PathStroke(cairo_t* cairoContext, Color color, double thickness)
				{
					cairo_set_line_width(cairoContext, 1.0);
					cairo_stroke(cairoContext);
				}

				WString WebdingsMap(WString oldString)
				{
					wchar_t result[oldString.Length() + 1];
					result[oldString.Length()] = L'\0';
					for(vint i = 0; i < oldString.Length(); i++)
					{
						switch(oldString[i])
						{
							case L'a': result[i] = 0x2713;
								break;
						}
					}
					return WString(result);
				}
			}
		}
	}
}
