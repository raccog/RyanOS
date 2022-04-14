#include "efi.h"

EfiStatus status;

// The main entry point for the UEFI bootloader.
EfiStatus EfiApi efi_main(EfiHandle image_handle, EfiSystemTable *st) {
    // Output string to console
    EfiChar16 *str = L"Hello UEFI!\n";
    status = st->console_out->output_string(st->console_out, str);
    if (status != EfiSuccess) {
        return status;
    }

    // Infinite loop to read output
    while (1) { }

    return EfiSuccess;
}

