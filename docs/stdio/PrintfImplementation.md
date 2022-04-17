# Printf Implementation

This document describes the libc implementation of printf.

## %-Based, No Formatting

This implementation will be the first version of printf.
It is based off the GNU libc printf formatting implementation that uses the '%' character to insert variables.
The following example shows a few simple calls to the printf used in my libc:

```c
printf("Hello %s%c\n", "world", '!');
printf("Hex: %x\n", 0xdeadbeef);
printf("Int: %d\n", -123456);
printf("Unsigned int: %u\n", 123456);
```

Unlike the GNU version, this implementation does not have formatting options such as specified whitespace, digits or alignment.
The following example is invalid and would not correctly insert the integer:

```c
printf("Invalid int: %05d\n);		// The marker '%05d' should instead be '%d'
```

## Memory Management

Ideally, the printf implementation used in the kernel and bootloader will not ever call malloc, and should only use stack allocated buffers.

### Implementation

When printf is called, the format string argument will be copied into a stack allocated buffer, one character at a time until one of the following happens:

1. A '%' character is encountered
2. The stack allocated buffer is full

In either case, the entire buffer will be printed out at this point.

### Variable Inserting

If a '%' character is encountered, the following character will be used to insert a variable.
The following characters can be used:

* % (enters a raw percent character; not a variable)
* d or i - i32
* u  - u32
* s - string
* c - char
* x - u32 hex
* p - u64 hex

### Variable Formatting

When a variable is inserted, it needs to be converted into a string before it is printed out (string or character variables excluded).

Each variable uses its own buffer separated from the format string buffer to be converted to a string.
These buffers need to be large enough to contain the largest possible value of each type.
