#pragma once
#include <cstdint>


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

    static const uint16_t STATIC_ROM    = 0x0000;
    static const uint16_t SWITCH_ROM    = 0x4000;
    static const uint16_t VRAM          = 0x8000;
    static const uint16_t SWITCH_RAM    = 0xA000;
    static const uint16_t SYSTEM_RAM    = 0xC000;
    static const uint16_t RAM_SHADOW    = 0xE000;
    static const uint16_t SPRITE_ATTR   = 0xFE00;
    static const uint16_t EMPTY_MEM_1   = 0xFEA0;
    static const uint16_t IO_PORTS      = 0xFF00;
    static const uint16_t EMPTY_MEM_2   = 0xFF4C;
    static const uint16_t ZERO_PAGE     = 0xFF80;
    static const uint16_t INTERRUPT     = 0xFFFF;
};