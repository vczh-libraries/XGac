#include "XlibNativeController.h"
#include "ServicesImpl/XlibNativeWindowService.h"
#include "ServicesImpl/XlibNativeScreenService.h"
#include "ServicesImpl/XlibNativeResourceService.h"
#include "../Common/ServicesImpl/PosixAsyncService.h"

#include "XlibIncludes.h"
#include "ServicesImpl/XlibNativeInputService.h"
#include "ServicesImpl/XlibNativeCallbackService.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				class XlibNativeController : public Object, public virtual INativeController
				{
				protected:
					//Xlib Display
					Display *display;

					//Native Services
					XlibNativeCallbackService *callbackService;
					XlibNativeResourceService *resourceService;
					PosixAsyncService *asyncService;
					INativeClipboardService *clipboardService;
					INativeImageService *imageService;
					XlibNativeScreenService *screenService;
					XlibNativeWindowService *windowService;
					XlibNativeInputService *inputService;
					INativeDialogService *dialogService;

				public:
					XlibNativeController(const char *displayString = NULL)
					{
						XSetErrorHandler(NULL);
						display = XOpenDisplay(displayString);
						if(!display)
						{
							throw Exception(L"Unable to open display.");
						}

						asyncService = new PosixAsyncService();
						//screenService = new XlibNativeScreenService(display);
						inputService = new XlibNativeInputService();
						windowService = new XlibNativeWindowService(display, asyncService);
						callbackService = new XlibNativeCallbackService();
						resourceService = new XlibNativeResourceService();
					}

					virtual ~XlibNativeController()
					{
						XCloseDisplay(display);
					}

					virtual INativeCallbackService *CallbackService()
					{
						return callbackService;
					}

					virtual INativeResourceService *ResourceService()
					{
						return resourceService;
					}

					virtual INativeAsyncService *AsyncService()
					{
						return asyncService;
					}

					virtual INativeClipboardService *ClipboardService()
					{
						//TODO
						return NULL;
					}

					virtual INativeImageService *ImageService()
					{
						//TODO
						return NULL;
					}

					virtual INativeScreenService *ScreenService()
					{
						//TODO
						return NULL;
					}

					virtual INativeWindowService *WindowService()
					{
						return windowService;
					}

					virtual INativeInputService *InputService()
					{
						return inputService;
					}

					virtual INativeDialogService *DialogService()
					{
						//TODO
						return NULL;
					}

					virtual WString GetOSVersion()
					{
						return WString(L"Linux");
					}

					virtual WString GetExecutablePath()
					{
						//TODO
						return WString();
					}
				};

				vl::presentation::INativeController *CreateXlibCairoNativeController(const char *displayname)
				{
					return new XlibNativeController(displayname);
				}


				void DestroyXlibCairoNativeController(vl::presentation::INativeController *controller)
				{
					delete controller;
				}


				void X11CairoMain()
				{
					GuiApplicationMain();
				}

			}
		}
	}
}
