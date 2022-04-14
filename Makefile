TARGET = x86_64-pc-unknown-windows
CFLAGS = -ffreestanding -fno-stack-protector -fno-stack-check \
		 -fshort-wchar -mno-red-zone -Wall -include libc/std.h

BOOT_CFLAGS = $(CFLAGS) -target $(TARGET) -std=c11 -g
BOOT_LDFLAGS = -target $(TARGET) -nostdlib -Wl,-entry:efi_main \
	-Wl,-subsystem:efi_application -fuse-ld=lld-link-14

BINDIR = build
SYSROOT = $(BINDIR)/sysroot
BOOTDIR = $(SYSROOT)/EFI/Boot
EFI_IMAGE = $(BOOTDIR)/Bootx64.efi

CACHEDIR = .cache
OVMF = OVMF.fd

BOOT_SRC = bootloader/entry.c \
		   libc/memset.c
BOOT_OBJ = $(patsubst %,$(BINDIR)/bootloader/%.o,$(BOOT_SRC))

.PHONY: all run

all: $(EFI_IMAGE)

run: $(EFI_IMAGE) $(CACHEDIR)/$(OVMF)
	echo "UEFI bootloader running..."
	qemu-system-x86_64 \
		-nographic \
		-bios $(CACHEDIR)/$(OVMF) \
		-net none \
		-drive file=fat:rw:$(SYSROOT),media=disk,format=raw \
		-m 128M

$(CACHEDIR)/$(OVMF):
	mkdir $(CACHEDIR)
	wget https://retrage.github.io/edk2-nightly/bin/DEBUGX64_OVMF.fd
	mv DEBUGX64_OVMF.fd $@

$(EFI_IMAGE): $(BOOT_OBJ)
	mkdir -p $(@D)
	clang-14 $(BOOT_LDFLAGS) -o $@ $^

$(BINDIR)/bootloader/%.c.o: %.c
	mkdir -p $(@D)
	clang-14 $(BOOT_CFLAGS) -Ilibc -c -o $@ $<


