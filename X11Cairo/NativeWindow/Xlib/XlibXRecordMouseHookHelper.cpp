#include "XlibXRecordMouseHookHelper.h"

namespace vl
{
	using namespace collections;
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				XlibXRecordMouseHookHelper::XlibXRecordMouseHookHelper(const char* connString):
					ctrlDisplay(NULL), dataDisplay(NULL), capturing(false)
				{
					hookEvents.SetLessMemoryMode(false);

					ctrlDisplay = XOpenDisplay(connString);
					dataDisplay = XOpenDisplay(connString);

					if(!ctrlDisplay || !dataDisplay)
					{
						throw Exception(L"Cannot connect to X server.");
					}

					if(!CheckXRecordExtension(ctrlDisplay) || !CheckXRecordExtension(dataDisplay))
					{
						throw Exception(L"Record Extension is required for GacUI/X11.");
					}
					
					// Initialize X Record Extension
					XRecordClientSpec recordClientSpec = XRecordAllClients;
					XRecordRange *recordRange = XRecordAllocRange();
					recordRange->device_events.first = ButtonPress;
					recordRange->device_events.last = MotionNotify;

					XSynchronize(ctrlDisplay, XLIB_TRUE);
					recordContext = XRecordCreateContext(ctrlDisplay, XRecordFromClientTime, &recordClientSpec, 1, &recordRange, 1);
					XFree(recordRange);
				}

				XlibXRecordMouseHookHelper::~XlibXRecordMouseHookHelper()
				{
					if(capturing) EndCapture();
					XRecordFreeContext(ctrlDisplay, recordContext);
					XFlush(dataDisplay);
					XCloseDisplay(ctrlDisplay);
					XCloseDisplay(dataDisplay);
				}

				void XlibXRecordMouseHookHelper::StartCapture()
				{
					XRecordEnableContextAsync(
							dataDisplay, 
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

					XFlush(dataDisplay);
					capturing = true;
				}

				void XlibXRecordMouseHookHelper::EndCapture()
				{
					XRecordDisableContext(ctrlDisplay, recordContext);
					capturing = false;
				}

				bool XlibXRecordMouseHookHelper::IsCapturing()
				{
					return capturing;
				}

				void XlibXRecordMouseHookHelper::Update()
				{
					XRecordProcessReplies(dataDisplay);
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

				void XlibXRecordMouseHookHelper::ProcessEvents(Func<void(MouseEvent)> handler)
				{
					Array<MouseEvent> currentEvents(hookEvents.Count());
				   	CopyFrom(currentEvents, hookEvents);

					FOREACH(MouseEvent, i, currentEvents)
					{
						handler(i);
					}

					hookEvents.Clear();
				}
			}
		}
	}
}
