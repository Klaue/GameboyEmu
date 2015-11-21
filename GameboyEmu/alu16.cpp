#include "cpu.h"

/*=================================================
16-BIT ARITHMETIC LOGIC UNIT
=================================================*/

/* ADD HL,n
Increments HL by the 16-bit value n
*/
inline void CPU::ADD16_HL_r2(uint16_t r2)
{
    uint16_t tempHL = HL;
    tempHL += r2;
    H = (tempHL & 0xFF00) >> 8;
    L = (tempHL & 0x00FF);
    F = (F & ZERO_FLAG)
        | ((r2 & 0x0FFF) > (tempHL & 0x0FFF) ? HALF_CARRY_FLAG : 0)
        | (r2 > tempHL ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region ADD_HL,n Implementations
void CPU::ADD16_HL_BC()
{
    ADD16_HL_r2(BC);
}

void CPU::ADD16_HL_DE()
{
    ADD16_HL_r2(DE);
}

void CPU::ADD16_HL_HL()
{
    ADD16_HL_r2(HL);
}

void CPU::ADD16_HL_SP()
{
    ADD16_HL_r2(SP);
}
#pragma endregion Adds 16-bit value to register_HL




/* ADD SP,n
Adds 8-bit immediate value to stack pointer.
*/
void CPU::ADD16_SP_n()
{
    unsigned char r2 = mem->read8(PC++);
    SP += r2;
    F = ((r2 & 0x0FFF) > (SP & 0x0FFF) ? HALF_CARRY_FLAG : 0)
        | (r2 > SP ? CARRY_FLAG : 0);
    lastStepClk = 4;
}



/* INC nn
Increments 16-bit register by one.
*/
inline void CPU::INC16_r2(unsigned char & highByte, unsigned char & lowByte)
{
    uint16_t temp = (highByte << 8) | lowByte;
    ++temp;
    highByte = (temp & 0xFF00) >> 8;
    lowByte = (temp & 0x00FF);
    lastStepClk = 2;
}
#pragma region 16-bit INC Implementation
void CPU::INC16_BC()
{
    INC16_r2(B, C);
}

void CPU::INC16_DE()
{
    INC16_r2(D, E);
}

void CPU::INC16_HL()
{
    INC16_r2(H, L);
}

void CPU::INC16_SP()
{
    ++SP;
    lastStepClk = 2;
}
#pragma endregion Increments 16-bit register by one.



/* DEC nn
Decrements 16-bit register by one.
*/
void CPU::DEC16_r2(unsigned char & highByte, unsigned char & lowByte)
{
    uint16_t temp = (highByte << 8) | lowByte;
    --temp;
    highByte = (temp & 0xFF00) >> 8;
    lowByte = (temp & 0x00FF);
    lastStepClk = 2;
}
#pragma region 16-bit DEC Implementations
void CPU::DEC16_BC()
{
    DEC16_r2(B, C);
}

void CPU::DEC16_DE()
{
    DEC16_r2(D, E);
}

void CPU::DEC16_HL()
{
    DEC16_r2(H, L);
}

void CPU::DEC16_SP()
{
    --SP;
    lastStepClk = 2;
}
#pragma endregion Decrements 16-bit register by one.