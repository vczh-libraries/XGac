#include "XlibNativeController.h"
#include "ServicesImpl/XlibNativeWindowService.h"

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

                public:
	                XlibNativeController (const char *display = NULL)
	                {
	                }

	                virtual ~XlibNativeController ()
	                {
	                }

	                virtual INativeCallbackService *CallbackService ();

	                virtual INativeResourceService *ResourceService ();

	                virtual INativeAsyncService *AsyncService ();

	                virtual INativeClipboardService *ClipboardService ();

	                virtual INativeImageService *ImageService ();

	                virtual INativeScreenService *ScreenService ();

	                virtual INativeWindowService *WindowService ();

	                virtual INativeInputService *InputService ();

	                virtual INativeDialogService *DialogService ();

	                virtual WString GetOSVersion ();

	                virtual WString GetExecutablePath ();
                };
            }
        }
    }
}