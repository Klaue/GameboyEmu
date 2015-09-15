#pragma once
#include <cstdint>

#define STATIC_ROM    0x0000
#define SWITCH_ROM    0x4000
#define VRAM        0x8000
#define SWITCH_RAM    0xA000
#define SYSTEM_RAM    0xC000
#define RAM_SHADOW    0xE000
#define SPRITE_ATTR 0xFE00
#define EMPTY_MEM_1    0xFEA0
#define IO_PORTS    0xFF00
#define EMPTY_MEM_2 0xFF4C
#define ZERO_PAGE    0xFF80
#define INTERRUPT    0xFFFF

class MMU {
public:
    //Constructor
    MMU();
    //Destructor
    ~MMU();

    /*=======================================
                    READS
    ========================================*/
    
    //Reads 8 bits from the location specified by addr
    unsigned char read8(uint16_t addr);
    //Reads 16 bits from the location specified by addr
    uint16_t read16(uint16_t addr);

    /*======================================
                    WRITES
    ========================================*/

    //Writes the 8-bit value val to the location specified by addr
    void write8(uint16_t addr, unsigned char val);
    //Writes the 16-bit value val to the location specified by addr.
    void write16(uint16_t addr, uint16_t val);
};