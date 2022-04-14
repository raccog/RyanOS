# RyanOS
A hobby operating system to just mess around with different concepts and have fun.

## Project Structure

The UEFI bootloader is currently in very early development and the structure of this project is still being fleshed out.

Description of sub-directories:

* `docs` - Will contain project documentation
* `bootloader` - Contains the UEFI bootloader
* `libc` - Contains c standard library
* `toolchain` - Scripts used to build a toolchain

## LibC

LibC will be compiled separately for use in the kernel, bootloader, and userspace.