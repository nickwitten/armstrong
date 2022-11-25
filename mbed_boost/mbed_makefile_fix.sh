#!/bin/bash
echo $1;
# Remove ld flags that wrap printfs
sed -i 's/^LD_FLAGS :=-Wl.*$/LD_FLAGS :=-Wl,--gc-sections -Wl,--wrap,main -mcpu=cortex-m3 -mthumb/' $1
# Remove mbed_config.h include in ASM_FLAGS
sed -i 's/^ASM_FLAGS += -include$//' $1
sed -i 's,^ASM_FLAGS += /filer/workspace_data/exports/c/c12a4c2f64f3ac1d2e90dbd0bfbbbcda/mbed_template/mbed_config.h$,,' $1
# Change the name to mbed
sed -i 's/PROJECT := mbed_template/PROJECT := mbed/' $1

