#include "XlibMouseRecordHelper.h"

namespace vl
{
	namespace presentation
	{
		namespace x11cairo
		{
			namespace xlib
			{
				XlibMouseRecordHelper::XlibMouseRecordHelper(const char* connString):
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
					recordRange->device_events.last = ButtonPress;

					XSynchronize(ctrl_display, XLIB_TRUE);
					recordContext = XRecordCreateContext(ctrl_display, XRecordFromClientTime, &recordClientSpec, 1, &recordRange, 1);
					XFree(recordRange);
				}

				XlibMouseRecordHelper::~XlibMouseRecordHelper()
				{
					if(capturing) EndCapture();
					XRecordFreeContext(ctrl_display, recordContext);
					XFlush(data_display);
					XCloseDisplay(ctrl_display);
					XCloseDisplay(data_display);
				}

				void XlibMouseRecordHelper::StartCapture()
				{
					XRecordEnableContextAsync(
							data_display, 
							recordContext, 
							[](XPointer closure, XRecordInterceptData *recorded_data)
							{
								if(recorded_data->category == XRecordFromServer)
								{
									xEvent *data = (xEvent *) recorded_data->data;
									if(data->u.u.type == ButtonPress)
									{
										printf("%d %d\n", data->u.keyButtonPointer.rootX, data->u.keyButtonPointer.rootY);
									}
								}
								XRecordFreeData(recorded_data);
							}, 
							(XPointer) this);

					XFlush(data_display);
					capturing = true;
				}

				void XlibMouseRecordHelper::EndCapture()
				{
					XRecordDisableContext(ctrl_display, recordContext);
					capturing = false;
				}

				bool XlibMouseRecordHelper::IsCapturing()
				{
					return capturing;
				}

				int XlibMouseRecordHelper::EventCount()
				{
					return hookEvents.Count();
				}

				Point XlibMouseRecordHelper::GetEvent()
				{
					return Point();
				}

				void XlibMouseRecordHelper::Update()
				{
					XRecordProcessReplies(data_display);
				}
			}
		}
	}
}
