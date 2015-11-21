#include "cpu.h"


/*=================================================
16-BIT LOADS
=================================================*/

/* LD n,nn (16-bit)
Loads the immediate 16-bit value into combined 16-bit register n.
*/
//Optimizable?
inline void CPU::LD16_n_nn(unsigned char & b1, unsigned char & b2)
{
    uint16_t immediateValue = mem->read16(PC);
    b1 = immediateValue >> 8;
    b2 = immediateValue & 0x00FF;
    PC += 2;
    lastStepClk = 3;
}
#pragma region LD_n_nn(b1, b2) Implementations
void CPU::LD16_BC_nn()
{
    LD16_n_nn(B, C);
}

void CPU::LD16_DE_nn()
{
    LD16_n_nn(D, E);
}

void CPU::LD16_HL_nn()
{
    LD16_n_nn(H, L);
}

//Of course, the stack pointer is not a combined register. It is naturally 16 bits.
void CPU::LD16_SP_nn()
{
    SP = mem->read16(PC);
    PC += 2;
    lastStepClk = 3;
}
#pragma endregion Operations for loading 16-bit immediate values.

void CPU::LD_SP_HL()
{
    SP = HL;
    lastStepClk = 2;
}

void CPU::LDHL_SP_n()
{
    uint16_t temp = SP + mem->read8(PC++);
    H = temp >> 8;
    L = temp & 0x00FF;
    lastStepClk = 3;
}

void CPU::LD_nn_SP()
{
    mem->write16(mem->read16(PC), SP);
    PC += 2;
    lastStepClk = 5;
}


/* PUSH nn
Pushes the combined 16-bit register onto the stack.
*/
inline void CPU::PUSH_nn(uint16_t nn)
{
    mem->write8(SP, nn);
    SP -= 2;
    lastStepClk = 4;
}
#pragma region Push Implementations
void CPU::PUSH_AF()
{
    PUSH_nn(AF);
}

void CPU::PUSH_BC()
{
    PUSH_nn(BC);
}

void CPU::PUSH_DE()
{
    PUSH_nn(DE);
}

void CPU::PUSH_HL()
{
    PUSH_nn(HL);
}
#pragma endregion Push 16-bit registers onto stack




/* POP nn
Pops 16 bits off the stack into a 16-bit combined register.
*/
inline void CPU::POP_nn(unsigned char & b1, unsigned char & b2)
{
    uint16_t temp = mem->read16(SP);
    b1 = temp >> 8;
    b2 = temp & 0x00FF;
    SP += 2;
    lastStepClk = 3;
}
#pragma region Pop Implementations
void CPU::POP_AF()
{
    POP_nn(A, F);
}

void CPU::POP_BC()
{
    POP_nn(B, C);
}

void CPU::POP_DE()
{
    POP_nn(D, E);
}

void CPU::POP_HL()
{
    POP_nn(H, L);
}
#pragma endregion Pop 16 bits off the stack and store into a 16-bit combined register.