#include "memory_map.h"

// Memory descriptor type strings
static const char *MEMORY_MAP_KIND[] = {
    "Free",
    "Reclaimable",
    "Reserved",
    "Loader",
    "Kernel"
};

void output_memory_map(const OSMemoryMap *map) {
    // Print memory map details

}

void to_os_memory_map(const EfiMemoryMap *efi_map, OSMemoryMap *os_map) {

}
