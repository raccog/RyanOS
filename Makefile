TARGET = x86_64-pc-unknown-windows
CFLAGS = -ffreestanding -fno-stack-protector -fno-stack-check \
		 -fshort-wchar -mno-red-zone -Wall -include std.h

BOOT_CFLAGS = $(CFLAGS) -target $(TARGET) -std=c11
BOOT_LDFLAGS = -flavor link -subsystem:efi_application -entry:efi_main

BINDIR = build
SYSROOT = $(BINDIR)/sysroot
BOOTDIR = $(SYSROOT)/EFI/Boot
EFI_IMAGE = $(BOOTDIR)/Bootx64.efi

CACHEDIR = .cache
OVMF = OVMF.fd

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

$(EFI_IMAGE): $(BINDIR)/entry.c.o $(BINDIR)/memset.c.o
	mkdir -p $(@D)
	lld-link-14 $(BOOT_LDFLAGS) -out:$@ $^

$(BINDIR)/entry.c.o: entry.c
	mkdir -p $(@D)
	clang-14 $(BOOT_CFLAGS) -Ilibc -c -o $@ $<

$(BINDIR)/memset.c.o: libc/memset.c
	clang-14 $(BOOT_CFLAGS) -Ilibc -c -o $@ $<


