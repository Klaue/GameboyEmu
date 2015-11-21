#include "cpu.h"


/*=================================================
MISCELLANEOUS
=================================================*/

/* SWAP n
Swaps lower and upper nybbles of 8-bit register n.
*/
inline void CPU::SWAP_r(unsigned char & r)
{
    r = ((r & 0xF0) >> 4) | ((r & 0x0F) << 4);
    F = (r ? 0 : ZERO_FLAG);
    lastStepClk = 2;
}
#pragma region SWAP Implementations
void CPU::SWAP_A()
{
    SWAP_r(A);
}

void CPU::SWAP_B()
{
    SWAP_r(B);
}

void CPU::SWAP_C()
{
    SWAP_r(C);
}

void CPU::SWAP_D()
{
    SWAP_r(D);
}

void CPU::SWAP_E()
{
    SWAP_r(E);
}

void CPU::SWAP_H()
{
    SWAP_r(H);
}

void CPU::SWAP_L()
{
    SWAP_r(L);
}

void CPU::SWAP_pHL()
{
    unsigned char r = mem->read8(HL);
    F = (r ? 0 : ZERO_FLAG);
    mem->write8(HL, ((r & 0xF0) >> 4) | ((r & 0x0F) << 4));
    lastStepClk = 4;
}
#pragma endregion Swaps lower and upper nybbles of register.


/* DAA
Corrects accumulator into proper BCD format.
*/
void CPU::DAA()
{
    //If the lower nybble of A is greater than 9, or the half carry flag is set...
    if (((A & 0x0F) > 0x09) || (F & HALF_CARRY_FLAG)) { A += 0x06; }
    //If the upper nybble of A is greater than 9, or the carry flag is set...
    if (((A & 0xF0) > 0x90) || (F & CARRY_FLAG))
    {
        A += 0x60;
        F = (A ? 0 : ZERO_FLAG) | (F & SUBTRACT_FLAG) | CARRY_FLAG;
    }
    else { F = (A ? 0 : ZERO_FLAG) | (F & SUBTRACT_FLAG); }
    lastStepClk = 1;
}


/* CPL
Complements all the bits in the accumulator.
*/
void CPU::CPL()
{
    A = ~A;
    F = (F & ZERO_FLAG) | SUBTRACT_FLAG | HALF_CARRY_FLAG | (F & CARRY_FLAG);
    lastStepClk = 1;
}


/* CCL
Complements the carry flag bit.
*/
void CPU::CCL()
{
    F = (!(F & CARRY_FLAG)) | (F & ZERO_FLAG);
    lastStepClk = 1;
}


/* SCF
Sets the carry flag bit.
*/
void CPU::SCF()
{
    F = CARRY_FLAG | (F & ZERO_FLAG);
    lastStepClk = 1;
}


/* NOP
Nuh-uh. Nah. Negative.
*/
void CPU::NOP()
{
    lastStepClk = 1;
}


/* HALT
Halts the processor until the next interrupt.
*/
void CPU::HALT()
{
    if (IME) { halted = true; }
#ifndef GAMEBOY_COLOR
    else { ++PC; }
#endif
    lastStepClk = 1;
}


/* STOP
Stops the CPU until a button is pressed.
*/
void CPU::STOP()
{
    stopped = true;
    lastStepClk = 1;
}


/* DI
Disables master interrupt flag after next instruction.
*/
void CPU::DI()
{
    IMETransitionCounter = 1;
    setToEnable = false;
    lastStepClk = 1;
}


/* EI
Enables master interrupt flag after next instruction.
*/
void CPU::EI()
{
    IMETransitionCounter = 1;
    setToEnable = true;
    lastStepClk = 1;
}