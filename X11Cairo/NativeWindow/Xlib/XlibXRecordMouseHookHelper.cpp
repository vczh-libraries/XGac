#include "XlibXRecordMouseHookHelper.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				XlibXRecordMouseHookHelper::XlibXRecordMouseHookHelper(const char* connString):
					ctrl_display(NULL), data_display(NULL), capturing(false)
				{
					ctrl_display = XOpenDisplay(connString);
					data_display = XOpenDisplay(connString);
					if(!ctrl_display || !data_display)
					{
						throw Exception(L"Cannot connect to X server.");
					}

					if(!CheckXRecordExtension(ctrl_display) || !CheckXRecordExtension(data_display))
					{
						throw Exception(L"Record Extension is required for GacUI/X11.");
					}
					
					// Initialize X Record Extension
					XRecordClientSpec recordClientSpec = XRecordAllClients;
					XRecordRange *recordRange = XRecordAllocRange();
					recordRange->device_events.first = ButtonPress;
					recordRange->device_events.last = MotionNotify;

					XSynchronize(ctrl_display, XLIB_TRUE);
					recordContext = XRecordCreateContext(ctrl_display, XRecordFromClientTime, &recordClientSpec, 1, &recordRange, 1);
					XFree(recordRange);
				}

				XlibXRecordMouseHookHelper::~XlibXRecordMouseHookHelper()
				{
					if(capturing) EndCapture();
					XRecordFreeContext(ctrl_display, recordContext);
					XFlush(data_display);
					XCloseDisplay(ctrl_display);
					XCloseDisplay(data_display);
				}

				void XlibXRecordMouseHookHelper::StartCapture()
				{
					XRecordEnableContextAsync(
							data_display, 
							recordContext, 
							[](XPointer closure, XRecordInterceptData *recorded_data)
							{
								if(recorded_data->category == XRecordFromServer)
								{
									xEvent *data = (xEvent *) recorded_data->data;
									XlibXRecordMouseHookHelper* helper = (XlibXRecordMouseHookHelper*) closure;
									switch(data->u.u.type)
									{
									case ButtonPress:
									case ButtonRelease:
									case MotionNotify:
										helper->AddData(data);
										break;
									}
								}
								XRecordFreeData(recorded_data);
							}, 
							(XPointer) this);

					XFlush(data_display);
					capturing = true;
				}

				void XlibXRecordMouseHookHelper::EndCapture()
				{
					XRecordDisableContext(ctrl_display, recordContext);
					capturing = false;
				}

				bool XlibXRecordMouseHookHelper::IsCapturing()
				{
					return capturing;
				}

				int XlibXRecordMouseHookHelper::EventCount()
				{
					return hookEvents.Count();
				}

				MouseEvent XlibXRecordMouseHookHelper::GetEvent()
				{
					MouseEvent ev = hookEvents[hookEvents.Count() - 1];
					hookEvents.RemoveAt(hookEvents.Count() - 1);
					return ev;
				}

				void XlibXRecordMouseHookHelper::Update()
				{
					XRecordProcessReplies(data_display);
				}

				MouseEvent XlibXRecordMouseHookHelper::DataToEvent(xEvent* ev)
				{
					MouseEventType type;
					MouseButton button;
					switch(ev->u.u.type)
					{
						case ButtonPress:
							type = MouseEventType::BUTTONDOWN;
							break;
						case ButtonRelease:
							type = MouseEventType::BUTTONUP;
							break;
						case MotionNotify:
							type = MouseEventType::POINTERMOVE;
							break;
					}

					if(ev->u.keyButtonPointer.state & Button2Mask)
					{
						button = MouseButton::RBUTTON;
					}
					else
					{
						button = MouseButton::LBUTTON;
					}

					return MouseEvent(button, type, ev->u.keyButtonPointer.rootX, ev->u.keyButtonPointer.rootY);
				}

				void XlibXRecordMouseHookHelper::AddData(xEvent* ev)
				{
					hookEvents.Add(DataToEvent(ev));
				}
			}
		}
	}
}
