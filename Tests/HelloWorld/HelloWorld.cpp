#include "HelloWorld.h"

template<typename T>
void RunWindow()
{
	GuiWindow* window = new T();
	GetApplication()->Run(window);
	delete window;
}

void GuiMain()
{
	RunWindow<HelloWorldWindow>();
}

int main(int argc, const char * argv[])
{
	SetupX11CairoRenderer();

	return 0;
}
