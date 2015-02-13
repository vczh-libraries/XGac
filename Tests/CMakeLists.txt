cmake_minimum_required(VERSION 2.8.12)
project(XGacTests)
find_package(PkgConfig REQUIRED)
include_directories("../Public/Source")
include_directories("../X11Cairo")

pkg_check_modules(DEPENDENCIES REQUIRED x11 cairo cairo-xlib pango pangocairo recordproto xtst)

include_directories(${DEPENDENCIES_INCLUDE_DIRS})
link_directories(${DEPENDENCIES_LIBRARY_DIRS})

set(OS_LIBRARIES "pthread")
if(APPLE)
    link_directories("/opt/X11/lib")
    link_directories("/usr/local/Cellar/gettext/0.19.3_1/lib")
    include_directories("/opt/X11/include")
	find_library(COREFOUNDATION_LIBRARIES CoreFoundation)
	set(OS_LIBRARIES ${COREFOUNDATION_LIBRARIES} ${OS_LIBRARIES})
	add_definitions(-D__APPLE__)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-missing-declarations")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_definitions(-DGAC_X11_DOUBLEBUFFER)

set(GACUI_COMMON_FILES "../Public/Source/Vlpp.cpp" "../Public/Source/VlppWorkflow.cpp" "../Public/Source/GacUI.cpp" "../Public/Source/GacUIReflection.cpp")

set(GACUI_X11CAIRO_COMMON_FILES
	"../X11Cairo/X11CairoSetup.cpp"
	"../X11Cairo/GraphicsElement/GuiGraphicsX11Cairo.cpp"
	"../X11Cairo/GraphicsElement/X11CairoRenderTarget.cpp"
	"../X11Cairo/GraphicsElement/X11CairoResourceManager.cpp"
	"../X11Cairo/GraphicsElement/Renderers/CairoHelpers.cpp"
	"../X11Cairo/GraphicsElement/Renderers/GuiSolidBackgroundElementRenderer.cpp"
	"../X11Cairo/GraphicsElement/Renderers/GuiSolidLabelElementRenderer.cpp"
	"../X11Cairo/GraphicsElement/Renderers/GuiSolidBorderElementRenderer.cpp"
	"../X11Cairo/GraphicsElement/Renderers/GuiGradientBackgroundElementRenderer.cpp"
	"../X11Cairo/GraphicsElement/Renderers/GuiPolygonElementRenderer.cpp"
	"../X11Cairo/NativeWindow/Common/ServicesImpl/PosixAsyncService.cpp"
	)

set(GACUI_X11CAIRO_XLIB_FILES
	"../X11Cairo/NativeWindow/Xlib/XlibNativeController.cpp"
	"../X11Cairo/NativeWindow/Xlib/XlibWindow.cpp"
	"../X11Cairo/NativeWindow/Xlib/XlibCommon.cpp"
	"../X11Cairo/NativeWindow/Xlib/XlibAtoms.cpp"
	"../X11Cairo/NativeWindow/Xlib/XlibScreen.cpp"
	"../X11Cairo/NativeWindow/Xlib/XlibXRecordMouseHookHelper.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeWindowService.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeScreenService.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeInputService.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeCallbackService.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeResourceService.cpp"
	)

add_library(GacUI STATIC ${GACUI_COMMON_FILES})
add_library(GacUIX11Cairo STATIC ${GACUI_X11CAIRO_COMMON_FILES} ${GACUI_X11CAIRO_XLIB_FILES})

set(DEPENDENCIES_LIBRARIES ${DEPENDENCIES_LIBRARIES} ${OS_LIBRARIES})
set(GACUI_LIBRARIES "GacUI" "GacUIX11Cairo")

set(HELLOWORLD_SOURCE_FILES "HelloWorld/HelloWorld.cpp")
add_executable(HelloWorld ${HELLOWORLD_SOURCE_FILES})
target_link_libraries(HelloWorld ${GACUI_LIBRARIES} ${DEPENDENCIES_LIBRARIES})

set(CONTROLS_BUTTON_ENABLEDISABLE_SOURCE_FILES "./Controls.Button.EnableDisable/Controls.Button.EnableDisable.cpp")
add_executable(Controls.Button.EnableDisable ${CONTROLS_BUTTON_ENABLEDISABLE_SOURCE_FILES})
target_link_libraries(Controls.Button.EnableDisable ${GACUI_LIBRARIES} ${DEPENDENCIES_LIBRARIES})

set(CONTROLS_BUTTON_CHECKANDRADIO_SOURCE_FILES "./Controls.Button.CheckAndRadio/Controls.Button.CheckAndRadio.cpp")
add_executable(Controls.Button.CheckAndRadio ${CONTROLS_BUTTON_CHECKANDRADIO_SOURCE_FILES})
target_link_libraries(Controls.Button.CheckAndRadio ${GACUI_LIBRARIES} ${DEPENDENCIES_LIBRARIES})

set(CONTROLS_LISTBOX_VIRTUALMODE_SOURCE_FILES "./Controls.ListBox.VirtualMode/Controls.ListBox.VirtualMode.cpp")
add_executable(Controls.ListBox.VirtualMode ${CONTROLS_LISTBOX_VIRTUALMODE_SOURCE_FILES})
target_link_libraries(Controls.ListBox.VirtualMode ${GACUI_LIBRARIES} ${DEPENDENCIES_LIBRARIES})

set(CONTROLS_LISTBOX_NAMESELECTOR_SOURCE_FILES "./Controls.ListBox.NameSelector/Controls.ListBox.NameSelector.cpp")
add_executable(Controls.ListBox.NameSelector ${CONTROLS_LISTBOX_NAMESELECTOR_SOURCE_FILES})
target_link_libraries(Controls.ListBox.NameSelector ${GACUI_LIBRARIES} ${DEPENDENCIES_LIBRARIES})

set(CONTROLS_SCROLL_COLORPICKER_SOURCE_FILES "./Controls.Scroll.ColorPicker/Controls.Scroll.ColorPicker.cpp")
add_executable(Controls.Scroll.ColorPicker ${CONTROLS_SCROLL_COLORPICKER_SOURCE_FILES})
target_link_libraries(Controls.Scroll.ColorPicker ${GACUI_LIBRARIES} ${DEPENDENCIES_LIBRARIES})

set(CONTROLS_DATEPICKER_DATEANDLOCALE_SOURCE_FILES "./Controls.DatePicker.DateAndLocale/Controls.DatePicker.DateAndLocale.cpp")
add_executable(Controls.DatePicker.DateAndLocale ${CONTROLS_DATEPICKER_DATEANDLOCALE_SOURCE_FILES})
target_link_libraries(Controls.DatePicker.DateAndLocale ${GACUI_LIBRARIES} ${DEPENDENCIES_LIBRARIES})

