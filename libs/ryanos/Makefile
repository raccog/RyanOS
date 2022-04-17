include $(CFGDIR)/default.mk
include $(CFGDIR)/bootloader.mk

RYANOS_BINDIR = $(BINDIR)/ryanos
RYANOS_SRCS = memory_map.c
BOOT_RYANOS_OBJS = $(patsubst %,$(RYANOS_BINDIR)/bootloader/%.o,$(RYANOS_SRCS))

.PHONY: all

all: $(RYANOS_LIBC)

$(RYANOS_LIBC): $(RYANOS_LIBC_OBJS)
	$(MKCWD)
	$(AR) rcs $@ $^

$(RYANOS_BINDIR)/bootloader/%.c.o: %.c
	$(MKCWD)
	$(CC) $(BOOT_CFLAGS) \
		-D__LIBRARY__='"BOOTRYANOS"' \
		-c -o $@ $<
