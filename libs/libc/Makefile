include $(CFGDIR)/default.mk
include $(CFGDIR)/bootloader.mk

LIBC_BINDIR = $(BINDIR)/libc
LIBC_H = string.h \
		 stdio.h \
		 stdlib.h \
		 stdlog.h
LIBC_SRCS = string.c \
			stdio.c \
			stdlib.c \
			stdlog.c
BOOT_LIBC_OBJS = $(patsubst %,$(LIBC_BINDIR)/bootloader/%.o,$(LIBC_SRCS))

.PHONY: all

all: $(BOOT_LIBC)

$(BOOT_LIBC): $(BOOT_LIBC_OBJS)
	$(MKCWD)
	$(AR) rcs $@ $^

$(LIBC_BINDIR)/bootloader/%.c.o: %.c $(LIBC_H)
	$(MKCWD)
	$(CC) $(BOOT_CFLAGS) \
		-D__LIBRARY__='"BOOTLIBC"' \
		-c -o $@ $<
