OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")

SEARCH_DIR(.)
SEARCH_DIR(./../ehal_latest/src)
SEARCH_DIR(./../ehal_latest/ARM/src)

SEARCH_DIR(./../sdk/ehal_latest/ARM/src)

GROUP(-lgcc -lc -lnosys -lCMSIS)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 16K
}

INCLUDE "gcc_arm_flash.ld"



