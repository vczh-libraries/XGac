#ifndef __XLIB_CAIRO_WINDOW_H
#define __XLIB_CAIRO_WINDOW_H

#include "XlibIncludes.h"
#include <GacUI.h>

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				class XlibCairoWindow : public Object, public INativeWindow
				{
				protected:
					Display *display;
					Window window;

				public:
					XlibCairoWindow(Display *display);

					virtual ~XlibCairoWindow();

					Display *GetDisplay();

					Window GetWindow();

					virtual Rect GetBounds();

					virtual void SetBounds(const Rect &bounds);

					virtual Size GetClientSize();

					virtual void SetClientSize(Size size);

					virtual Rect GetClientBoundsInScreen();

					virtual WString GetTitle();

					virtual void SetTitle(WString title);

					virtual INativeCursor *GetWindowCursor();

					virtual void SetWindowCursor(INativeCursor *cursor);

					virtual Point GetCaretPoint();

					virtual void SetCaretPoint(Point point);

					virtual INativeWindow *GetParent();

					virtual void SetParent(INativeWindow *parent);

					virtual bool GetAlwaysPassFocusToParent();

					virtual void SetAlwaysPassFocusToParent(bool value);

					virtual void EnableCustomFrameMode();

					virtual void DisableCustomFrameMode();

					virtual bool IsCustomFrameModeEnabled();

					virtual WindowSizeState GetSizeState();

					virtual void Show();

					virtual void ShowDeactivated();

					virtual void ShowRestored();

					virtual void ShowMaximized();

					virtual void ShowMinimized();

					virtual void Hide();

					virtual bool IsVisible();

					virtual void Enable();

					virtual void Disable();

					virtual bool IsEnabled();

					virtual void SetFocus();

					virtual bool IsFocused();

					virtual void SetActivate();

					virtual bool IsActivated();

					virtual void ShowInTaskBar();

					virtual void HideInTaskBar();

					virtual bool IsAppearedInTaskBar();

					virtual void EnableActivate();

					virtual void DisableActivate();

					virtual bool IsEnabledActivate();

					virtual bool RequireCapture();

					virtual bool ReleaseCapture();

					virtual bool IsCapturing();

					virtual bool GetMaximizedBox();

					virtual void SetMaximizedBox(bool visible);

					virtual bool GetMinimizedBox();

					virtual void SetMinimizedBox(bool visible);

					virtual bool GetBorder();

					virtual void SetBorder(bool visible);

					virtual bool GetSizeBox();

					virtual void SetSizeBox(bool visible);

					virtual bool GetIconVisible();

					virtual void SetIconVisible(bool visible);

					virtual bool GetTitleBar();

					virtual void SetTitleBar(bool visible);

					virtual bool GetTopMost();

					virtual void SetTopMost(bool topmost);

					virtual void SupressAlt();

					virtual bool InstallListener(INativeWindowListener *listener);

					virtual bool UninstallListener(INativeWindowListener *listener);

					virtual void RedrawContent();
				};
			}
		}
	}
}

#endif