#ifndef __HELLO_WORLD_H
#define __HELLO_WORLD_H

#include <GacUI.h>
#include "X11CairoIncludes.h"

using namespace vl;
using namespace vl::presentation;
using namespace vl::presentation::theme;
using namespace vl::presentation::controls;

class HelloWorldWindow : public GuiWindow
{
public:
	HelloWorldWindow() :GuiWindow(GetCurrentTheme()->CreateWindowStyle())
	{
		WString title(L"GacUI X11/Cairo");

		this->SetText(title);
		this->SetClientSize(vl::presentation::Size(640, 480));
		//this->MoveToScreenCenter();

		
		GuiControl* label = g::NewLabel();
		label->SetText(L"Welcome to GacUI Library!");
		{
			FontProperties font;
			font.fontFamily = L"Sans";
			font.size = 40;
			font.antialias = true;
			font.italic = true;
			font.underline = true;
			font.strikeline = true;
			font.bold = true;
			label->SetFont(font);
		}
		this->AddChild(label);
		
	}

	~HelloWorldWindow()
	{
	}
};

#endif
