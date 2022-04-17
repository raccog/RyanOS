BOOT_CFLAGS = -ffreestanding -fno-stack-protector -fno-stack-check \
		-fshort-wchar -mno-red-zone -Wall -Wextra \
		-I$(ROOTDIR)/libs/libc -I$(ROOTDIR)/libs/hw \
		-I$(ROOTDIR)/libs/ryanos \
		-include $(ROOTDIR)/libs/libc/std.h \
		-target $(TARGET) -std=c11 -g \
		-D__BOOTLOADER__
BOOT_LDFLAGS = -target $(TARGET) -nostdlib -Wl,-entry:efi_main \
	-Wl,-subsystem:efi_application -fuse-ld=lld-link-14

BOOT_BINDIR = $(BINDIR)/bootloader
BOOT_SRCS = entry.c
BOOT_OBJS = $(patsubst %,$(BOOT_BINDIR)/%.o,$(BOOT_SRCS))
BOOT_LIBC = $(BINDIR)/libc/libc-bootloader.a
BOOT_LIBS = $(BOOT_LIBC)
EFI_IMAGE = $(SYSROOT_BOOT)/Bootx64.efi

MKCWD = mkdir -p $(@D)
