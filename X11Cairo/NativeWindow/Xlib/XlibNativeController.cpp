#include "XlibNativeController.h"
#include "ServicesImpl/XlibNativeWindowService.h"
#include "ServicesImpl/XlibNativeScreenService.h"
#include "../Common/ServiceImpl/PosixAsyncService.h"

#include "XlibIncludes.h"

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
					INativeCallbackService *callbackService;
					INativeResourceService *resourceService;
					PosixAsyncService *asyncService;
					INativeClipboardService *clipboardService;
					INativeImageService *imageService;
					XlibNativeScreenService *screenService;
					XlibNativeWindowService *windowService;
					INativeInputService *inputService;
					INativeDialogService *dialogService;

				public:
					XlibNativeController(const char *displayString = NULL)
					{
						display = XOpenDisplay(displayString);

						asyncService = new PosixAsyncService();
						//screenService = new XlibNativeScreenService(display);
						windowService = new XlibNativeWindowService(display);
					}

					virtual ~XlibNativeController()
					{
						XCloseDisplay(display);
					}

					virtual INativeCallbackService *CallbackService()
					{
						//TODO
						return NULL;
					}

					virtual INativeResourceService *ResourceService()
					{
						//TODO
						return NULL;
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
						//TODO
						return NULL;
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

				INativeController *CreateXlibCairoNativeController(const char *displayname = NULL)
				{
					return new XlibNativeController(displayname);
				}


				void DestroyXlibCairoNativeController(INativeController *controller)
				{
					delete controller;
				}


				void X11CairoMain();

			}
		}
	}
}