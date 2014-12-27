#include <X11/Xlib.h>
#include <GacUI.h>

namespace vl
{
    namespace presentation
    {
        namespace x11cairo
        {
            namespace xlib
            {
				class XlibNativeWindowService: public Object, public virtual INativeWindowService
				{
				protected:
					Display* display;

				public:
					XlibNativeWindowService (const char *display = NULL);

					~XlibNativeWindowService ();

					virtual INativeWindow *CreateNativeWindow ();

					virtual void DestroyNativeWindow (INativeWindow *window);

					virtual INativeWindow *GetMainWindow ();

					virtual INativeWindow *GetWindow (Point location);

					virtual void Run (INativeWindow *window);
				};
            }
        }
    }
}
