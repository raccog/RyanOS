#pragma once

#include "efi/efi.h"

typedef u64 OSMemoryAddress;

// Types of memory descriptors
typedef enum {
    OSFree,
    OSReclaimable,
    OSReserved,
    OSLoader,
    OSKernel,
} OSMemoryKind;

// Description of a chunk of physical memory
typedef struct {
    OSMemoryKind kind;
    OSMemoryAddress start;
    size_t size;
} OSMemoryDescriptor;

typedef struct {
    OSMemoryDescriptor *descriptors;
    size_t entries;
} OSMemoryMap;

// Prints out an os memory map
void output_memory_map(const OSMemoryMap *map);

// Converts an efi memory map to an os memory map
void to_os_memory_map(const EfiMemoryMap *efi_map, OSMemoryMap *os_map);
