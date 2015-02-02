#include <signal.h>

#include "XlibAtoms.h"
#include "XlibNativeController.h"
#include "ServicesImpl/XlibNativeWindowService.h"
#include "ServicesImpl/XlibNativeScreenService.h"
#include "ServicesImpl/XlibNativeResourceService.h"
#include "ServicesImpl/XlibNativeInputService.h"
#include "ServicesImpl/XlibNativeCallbackService.h"
#include "../Common/ServicesImpl/PosixAsyncService.h"

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
						screenService = new XlibNativeScreenService(display);
						inputService = new XlibNativeInputService();
						callbackService = new XlibNativeCallbackService();
						windowService = new XlibNativeWindowService(display, asyncService, callbackService);
						resourceService = new XlibNativeResourceService();

						XlibAtoms::Initialize(display);

						if(signal(SIGALRM, XlibNativeController::TimerSignalHandler))
						{
							throw Exception(L"Unable to set signal handler");
						}
					}

					virtual ~XlibNativeController()
					{
						delete resourceService;
						delete windowService;
						delete callbackService;
						delete inputService;
						delete screenService;
						delete asyncService;

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
						return screenService;
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

					static void TimerSignalHandler(int signal)
					{
						if(XlibNativeController* controller = dynamic_cast<XlibNativeController*>(GetCurrentController()))
						{
							XlibNativeCallbackService* callbackService = dynamic_cast<XlibNativeCallbackService*>(controller->CallbackService());
							if(callbackService)
							{
								callbackService->SetTimer();
							}
						}
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
