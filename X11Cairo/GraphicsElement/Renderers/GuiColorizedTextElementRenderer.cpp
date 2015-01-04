#include "GuiColorizedTextElementRenderer.h"

using namespace vl::collections;
using namespace vl::presentation::elements::text;
namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			GuiColorizedTextElementRenderer::GuiColorizedTextElementRenderer()
				: minSize(1, 1), cairoContext(NULL), pangoFontDesc(NULL)
			{
			}

			void GuiColorizedTextElementRenderer::InitializeInternal()
			{
				pangoFontDesc = pango_font_description_new();
			}

			void GuiColorizedTextElementRenderer::FinalizeInternal()
			{
				pango_font_description_free(pangoFontDesc);
				if(attrList)
					pango_attr_list_unref(attrList);
			}

			void GuiColorizedTextElementRenderer::Render(Rect bounds)
			{
				if(cairoContext)
				{
					PangoLayout *layout = pango_cairo_create_layout(cairoContext);

					text::ColorEntry color = element->GetColors()[0];
					FontProperties font = element->GetFont();
					AString text = wtoa(element->GetLines().GetText());

					pango_layout_set_font_description(layout, pangoFontDesc);
					pango_layout_set_attributes(layout, attrList);
					pango_layout_set_text(layout, text.Buffer(), text.Length());

					cairo_set_source_rgb(cairoContext, 
							1.0 * color.normal.background.r / 255, 
							1.0 * color.normal.background.g / 255, 
							1.0 * color.normal.background.b / 255
							);
					cairo_rectangle(cairoContext, bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
					cairo_fill(cairoContext);
					
					cairo_set_source_rgb(cairoContext, 
							1.0 * color.normal.text.r / 255, 
							1.0 * color.normal.text.g / 255, 
							1.0 * color.normal.text.b / 255
							);

					cairo_move_to(cairoContext, bounds.x1, bounds.y1);
					pango_cairo_show_layout(cairoContext, layout);

					g_object_unref(layout);
				}
			}

			void GuiColorizedTextElementRenderer::OnElementStateChanged()
			{
				FontProperties font = element->GetFont();
				text::ColorEntry color = element->GetColors()[0];
				
				pango_font_description_set_family(pangoFontDesc, wtoa(font.fontFamily).Buffer());
				pango_font_description_set_size(pangoFontDesc, font.size);

				if(font.italic) pango_font_description_set_style(pangoFontDesc, PANGO_STYLE_ITALIC);
				else pango_font_description_set_style(pangoFontDesc, PANGO_STYLE_NORMAL);

				if(attrList)
				{
					pango_attr_list_unref(attrList);
				}

				attrList = pango_attr_list_new();
				
				pango_attr_list_insert(attrList, font.underline ?
					pango_attr_underline_color_new(
						color.normal.text.r,
						color.normal.text.g,
						color.normal.text.b) :
					pango_attr_underline_new(PANGO_UNDERLINE_NONE)
					);

				pango_attr_list_insert(attrList, pango_attr_strikethrough_new (
							font.strikeline ? TRUE : FALSE
							)
						);

			}

			void GuiColorizedTextElementRenderer::RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT)
			{
				if(cairoContext)
					cairo_destroy(cairoContext);
				if(newRT) cairoContext = cairo_create(newRT->GetCairoSurface());
			}
		}
	}
}
