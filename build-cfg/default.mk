TARGET = x86_64-pc-unknown-windows

BINDIR = $(ROOTDIR)/build
SYSROOT = $(BINDIR)/sysroot
SYSROOT_BOOT = $(SYSROOT)/EFI/Boot

CACHEDIR = .cache
OVMF = OVMF.fd

AR = llvm-ar-14
CC = clang-14

