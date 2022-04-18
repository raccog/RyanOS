# Initializing Stdio

Some type of console output should be initialized as early in the bootloader and kernel as possible.

Any errors or logs cannot be typically displayed to the user when there is no initialized console.
So any errors or logs that are emitted before the initialization completes will be lost (unless they are temporarily saved to RAM).

## Bootloader Stdio Initialization

The UEFI bootloader needs to initialize the console at runtime because it needs the UEFI system table that is passed as an argument to `efi_main`.
For this reason, any print function (such as `printf`) cannot assume that the console has already been set up because it could be called before the console initialization is complete.

### Assertions

Assert statements can be used to solve this, but there are two problems with this method:

1. In order to emit an error on a failed assertion, a console needs to be initialized. If the assertion fails before a console is initialized, there will be no way to emit the error.
2. Since assertions are called at runtime, some of these errors may take a long time to be caught.

The first problem can be solved by aborting the bootloader and returning an error code.
The UEFI shell might need to be invoked to read the error code.

The second problem is more difficult.
