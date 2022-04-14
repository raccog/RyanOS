#include <string.h>

#include "efi.h"

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
EfiStatus uefi_write_string(const char *str) {
    // TODO: Use more efficient algorithm
    while (*str != '\0') {
        uefi_write_character(*str);
        ++str;
    }
    return EfiSuccess;
}

// Returns status if it is not EfiSuccess
#define UEFI_CHECKSTATUS \
    if (status != EfiSuccess) { \
        return status; \
    }

// The main entry point for the UEFI bootloader.
EfiStatus EfiApi efi_main(EfiHandle image_handle, EfiSystemTable *st) {
    // Initialize console output
    console_out = st->console_out;

    // Output string to console
    const char *str = "Hello UEFI!\n";
    status = uefi_write_string(str);
    UEFI_CHECKSTATUS

    // Infinite loop to read output
    while (1) { }

    return EfiSuccess;
}

