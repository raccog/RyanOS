# RyanOS
A hobby operating system to just mess around with different concepts and have fun.
RyanOS is a temporary name that will be replaced in the future.

## Roadmap

A rough roadmap is described in [Roadmap.md](Roadmap.md).

## More Documentation

Documentation about other topics, including implementation details and specific planning, is in [docs/Index.md](docs/Index.md).

## Project Structure

The UEFI bootloader is currently in very early development and the structure of this project is still being fleshed out.

Description of sub-directories:

* `docs` - Will contain project documentation
* `bootloader` - Contains the UEFI bootloader
* `libc` - Contains c standard library
* `toolchain` - Scripts used to build a toolchain

### LibC

LibC will be compiled separately for use in the kernel, bootloader, and userspace.

### HW

HW includes hardware abstractions that are mostly used in the bootloader and kernel.
