# Iyon
---
A modern, simple, 64-bit Operating System

## About this project
I started out in OS dev around September 2021, doing a bit of work here and there until I started working on [MellOs](https://www.github.com/mell-o-tron/MellOs). It's certainly an amazing project and I really enjoyed it, but decided to go my own way and make something unique. I developed an OS called Eisen for a few months but ultimately became unhappy with the way I'd approached it, so it became time to start over and this is the result of that.

This couldn't have been made possible without the projects and resources listed in `Resources.md`. Please check them out!

## Contributing
Contributions are very welcome to the project!

To start contributing, run `setup-(your_os).sh` from the `setup` directory - this should install all the necessary packages and build environments required. From there, write whatever changes you want and run `make build` to compile the source code or `make run` to run the compiled OS. Alternatively, just run `make` to do both in one go.

While development is pretty open-ended, there are a few stylistic points to be adhered to:
- Use standard British English
- Use tabs (indent by 4 spaces)
- No langauges other than C and Assembly are to be used (AT&T syntax)
- C header files use `#pragma once` as guards
- Use LF, not CRLF

Here's a couple ideas of what to add to maybe get you started:
- Setup scripts for Windows, OSX, or your linux distro.
- Support for other languages (French, German, Spanish, and Italian are ideal but anything you can offer would be appreciated.)
- Device drivers for disks, sound, internet, whatever.