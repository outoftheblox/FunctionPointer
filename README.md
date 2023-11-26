# FunctionPointer
A function pointer. The idea was to use this to call static ISR routines on a ESP. This does not work since it can not have ICACHE_RAM_ATTR.