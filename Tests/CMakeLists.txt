cmake_minimum_required(VERSION 2.8.12)
project(XGacTests)
find_package(PkgConfig REQUIRED)
include_directories("../Public/Source")
include_directories("../X11Cairo")

pkg_check_modules(DEPENDENCIES REQUIRED x11 cairo cairo-xlib pango pangocairo)

include_directories(${DEPENDENCIES_INCLUDE_DIRS})
link_directories(${DEPENDENCIES_LIBRARY_DIRS})

if(APPLE)
    link_directories("/opt/X11/lib")
    link_directories("/usr/local/Cellar/gettext/0.19.3_1/lib")
    include_directories("/opt/X11/include")
    find_library(OS_LIBRARIES CoreFoundation)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__APPLE__")
else()
    set(OS_LIBRARIES)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(GACUI_COMMON_FILES "../Public/Source/Vlpp.cpp" "../Public/Source/VlppWorkflow.cpp" "../Public/Source/GacUI.cpp" "../Public/Source/GacUIReflection.cpp")

set(GACUI_X11CAIRO_COMMON_FILES
	"../X11Cairo/X11CairoSetup.cpp"
	"../X11Cairo/GraphicsElement/GuiGraphicsX11Cairo.cpp"
	"../X11Cairo/GraphicsElement/X11CairoRenderTarget.cpp"
	"../X11Cairo/GraphicsElement/X11CairoResourceManager.cpp"
	"../X11Cairo/GraphicsElement/Renderers/GuiSolidBackgroundElementRenderer.cpp"
	"../X11Cairo/GraphicsElement/Renderers/GuiSolidLabelElementRenderer.cpp"
	"../X11Cairo/NativeWindow/Common/ServicesImpl/PosixAsyncService.cpp"
	)

set(GACUI_X11CAIRO_XLIB_FILES
	"../X11Cairo/NativeWindow/Xlib/XlibNativeController.cpp"
	"../X11Cairo/NativeWindow/Xlib/XlibCairoWindow.cpp"
	"../X11Cairo/NativeWindow/Xlib/XlibScreen.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeWindowService.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeScreenService.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeInputService.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeCallbackService.cpp"
	"../X11Cairo/NativeWindow/Xlib/ServicesImpl/XlibNativeResourceService.cpp"
	)

set(HELLOWORLD_SOURCE_FILES HelloWorld.cpp)
add_executable(HelloWorld ${HELLOWORLD_SOURCE_FILES} ${GACUI_COMMON_FILES} ${GACUI_X11CAIRO_COMMON_FILES} ${GACUI_X11CAIRO_XLIB_FILES})
target_link_libraries(HelloWorld pthread ${DEPENDENCIES_LIBRARIES} ${OS_LIBRARIES})

