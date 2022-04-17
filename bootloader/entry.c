#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_map.h"
#include "efi/efi.h"

EfiStatus status;
EfiSimpleTextOutputProtocol *console_out; 

// Wrapper to write char to UEFI console output
EfiStatus uefi_write_character(char c) {
    EfiChar16 str[2];
    str[0] = (EfiChar16)c;
    str[1] = L'\0';
    return console_out->output_string(console_out, str);
}

// Wrapper to write string to UEFI console output
int uefi_write_string(const char *str) {
    // TODO: Use more efficient algorithm
    while (*str != '\0') {
        if (uefi_write_character(*str) != EfiSuccess) {
            return -1;
        }
        ++str;
    }
    return 0;
}

// Returns status if it is not EfiSuccess
#define UEFI_CHECKSTATUS \
    if (status != EfiSuccess) { \
        return status; \
    }

// The main entry point for the UEFI bootloader.
EfiStatus EfiApi efi_main(EfiHandle image_handle, EfiSystemTable *st) {
    EfiBootServices *bs = st->boot_services;

    // Initialize console output
    console_out = st->console_out;
    set_output(&uefi_write_string);

    // Output string to console
    const char *str = "Hello UEFI!\n";
    status = uefi_write_string(str);
    UEFI_CHECKSTATUS

    // Allocate pages with UEFI boot service
    EfiPhysicalAddress heap;
    status = bs->allocate_pages(AllocateMaxAddress, EfiLoaderData,
            100, &heap);    // Allocate 100 * 4KiB pages
    if (status != EfiSuccess) {
        printf("Failed to allocate pages...\n");
    }

    // Test malloc
    init_malloc((void *)heap, 100 * 4096);
    void *ptr1 = malloc(0xff);
    void *ptr2 = malloc(0xfe);
    void *ptr3 = malloc(0xff);
    printf("Ptr1: %p\nPtr2: %p\nPtr3: %p\n\n",
            ptr1, ptr2, ptr3);

    // Test printf
    printf("Hello %s%c\n", "world", '!');
    printf("Hex: %x\n", 0x1234abcd);
    printf("Hex max: %x\n", 0xffffffff);
    printf("Hex min: %x\n", 0x00000000);
    printf("Ptr: %p\n", 0x1234567890abcdef);
    printf("Ptr max: %p\n", 0xffffffffffffffff);
    printf("Ptr min: %p\n", 0x0);
    printf("Int: %d\n", -123456789);
    printf("Int max: %d\n", INT_MAX);
    printf("Int min: %d\n", INT_MIN);
    printf("Uint: %u\n", 123456789);
    printf("Uint max: %u\n", UINT_MAX);
    printf("Uint min: %u\n", 0);

    EfiHandle handles[100];
    uptr buffer_size = 100 * sizeof(EfiHandle);

    status = bs->locate_handle(ByProtocol, &EfiBlockIoProtocolGuid, NULL,
            &buffer_size, handles);
    printf("Number of handles received: %i\n", buffer_size / sizeof(EfiHandle));
    if (status == EfiNotFound) {
        printf("Failed to locate EfiLoadFileProtocol handle...\n");
    }

    // Infinite loop to read output
    while (1) { }

    return EfiSuccess;
}

