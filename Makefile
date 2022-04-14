ROOTDIR := $(shell pwd)
CFGDIR = $(ROOTDIR)/build-cfg
export ROOTDIR CFGDIR

include $(CFGDIR)/default.mk
include $(CFGDIR)/bootloader.mk

.PHONY: all run bootloader libc clean nuke

all: bootloader libc

clean:
	rm -rf build

nuke: clean
	rm -rf .cache

bootloader: libc
	make -C bootloader

libc:
	make -C libc

run: bootloader $(CACHEDIR)/$(OVMF)
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


