include $(CFGDIR)/default.mk
include $(CFGDIR)/bootloader.mk

.PHONY: all

all: $(EFI_IMAGE)

$(EFI_IMAGE): $(BOOT_OBJS) $(BOOT_LIBS)
	echo $(BOOT_OBJS)
	$(MKCWD)
	$(CC) $(BOOT_LDFLAGS) -o $@ $^

$(BOOT_BINDIR)/%.c.o: %.c
	$(MKCWD)
	$(CC) $(BOOT_CFLAGS) -c -o $@ $<
