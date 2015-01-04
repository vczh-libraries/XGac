#include "GuiSolidLabelElementRenderer.h"

using namespace vl::collections;
using namespace vl::presentation::elements::text;
namespace vl
{
	namespace presentation
	{
		namespace elements_x11cairo
		{
			GuiSolidLabelElementRenderer::GuiSolidLabelElementRenderer()
				: minSize(1, 1), cairoContext(NULL), pangoFontDesc(NULL), attrList(NULL)
			{
			}

			void GuiSolidLabelElementRenderer::InitializeInternal()
			{
				pangoFontDesc = pango_font_description_new();
			}

			void GuiSolidLabelElementRenderer::FinalizeInternal()
			{
				pango_font_description_free(pangoFontDesc);
				if(attrList)
					pango_attr_list_unref(attrList);
			}

			void GuiSolidLabelElementRenderer::Render(Rect bounds)
			{
				if(cairoContext)
				{
					PangoLayout *layout = pango_cairo_create_layout(cairoContext);

					Color color = element->GetColor();
					FontProperties font = element->GetFont();
					AString text = wtoa(element->GetText());

					pango_layout_set_font_description(layout, pangoFontDesc);
					pango_layout_set_attributes(layout, attrList);
					pango_layout_set_text(layout, text.Buffer(), text.Length());
					
					cairo_set_source_rgb(cairoContext, 
							1.0 * color.r / 255, 
							1.0 * color.g / 255, 
							1.0 * color.b / 255
							);

					cairo_move_to(cairoContext, bounds.x1, bounds.y1);
					pango_cairo_update_layout(cairoContext, layout);
					pango_cairo_show_layout(cairoContext, layout);

					g_object_unref(layout);
				}
			}

			void GuiSolidLabelElementRenderer::OnElementStateChanged()
			{
				FontProperties font = element->GetFont();
				Color color = element->GetColor();
				
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
						color.r,
						color.g,
						color.b) :
					pango_attr_underline_new(PANGO_UNDERLINE_NONE)
					);

				pango_attr_list_insert(attrList, pango_attr_strikethrough_new (
							font.strikeline ? TRUE : FALSE
							)
						);

			}

			void GuiSolidLabelElementRenderer::RenderTargetChangedInternal(IX11CairoRenderTarget* oldRT, IX11CairoRenderTarget* newRT)
			{
				if(cairoContext)
					cairo_destroy(cairoContext);
				if(newRT) cairoContext = cairo_create(newRT->GetCairoSurface());
			}
		}
	}
}
