include $(CFGDIR)/default.mk
include $(CFGDIR)/bootloader.mk

LIBC_BINDIR = $(BINDIR)/libc
LIBC_SRCS = string.c \
			stdio.c
BOOT_LIBC_OBJS = $(patsubst %,$(LIBC_BINDIR)/bootloader/%.o,$(LIBC_SRCS))

.PHONY: all

all: $(BOOT_LIBC)

$(BOOT_LIBC): $(BOOT_LIBC_OBJS)
	$(MKCWD)
	$(AR) rcs $@ $^

$(LIBC_BINDIR)/bootloader/%.c.o: %.c
	$(MKCWD)
	$(CC) $(BOOT_CFLAGS) -I$(ROOTDIR)/libc \
		-include $(ROOTDIR)/libc/std.h -c -o $@ $<
