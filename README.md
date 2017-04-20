# XGac: a X11/Cairo/Pango port of GacLib

[![Build Status](https://travis-ci.org/vczh-libraries/XGac.svg?branch=master)](https://travis-ci.org/vczh-libraries/XGac)

## License

**Read the [LICENSE](https://github.com/vczh-libraries/XGac/blob/master/LICENSE.md) first.**

Rendering components of XGac depends on [Cairo](http://cairographics.org/) and [Pango](http://www.pango.org/), which are licensed under the GNU Lesser General Public License (LGPL). Please follow the requirements of these libraries when distributing your application.

## Status

XGac is still in early development stage. It is definitely not ready for production usage.

Pull requests and issue reports are welcomed.

## Dependencies

- Xlib (libx11) with extensions
- Cairo and its Xlib backend
- Pango and its Cairo backend

## Requirements

Gaclib uses a global mouse hook to handle pop-up windows. To implement these hook function, XGac requires XRecord extension enabled on X Server.

XDBE (Double Buffer Extension) is used for double buffering. Without this extension XGac will still work but without double buffering.

## Build instructions

Included CMake makefiles can be used to build the examples on Linux/OSX systems.

Instructions on how to use XGac in production will be given once XGac reaches stable.

## TODOs

- Window related functions
- Bitmap/Image handling
- TextBox/RichTextEditor renderer
- Multi-monitor handling (Xinerama/Xrandr)
- Cairo-GL based, hardware accelerated backend
- Input method support

## Known issues

- Double buffering causes problem while resizing windows
- Pop-up windows flash on left-top under XQuartz before showing up on right position
- Pop-up windows would not hide in Window Manager's list
- Pop-up windows would not keep on top of stack
