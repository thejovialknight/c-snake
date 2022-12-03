This repo requires CMAKE to be installed.

- sudo apt install cmake

It also requires YCM to be compiled with clangd

- python3 install.py --clangd-completer in /plugged/YouCompleteMe/
- Also requires a symlink between the exported compile stuff from /build to the root of the project hierarchy. This is because YCM expects compiler flags or whatever to be in the top level directory.
