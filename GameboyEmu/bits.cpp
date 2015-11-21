#include "cpu.h"


/*=================================================
BIT TESTS
=================================================*/

void CPU::BIT_r_0(unsigned char r)
{
    F = ((r & 0x01) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region BIT_r_0 implementations
void CPU::BIT_A_0()
{
    BIT_r_0(A);
}

void CPU::BIT_B_0()
{
    BIT_r_0(B);
}

void CPU::BIT_C_0()
{
    BIT_r_0(C);
}

void CPU::BIT_D_0()
{
    BIT_r_0(D);
}

void CPU::BIT_E_0()
{
    BIT_r_0(E);
}

void CPU::BIT_H_0()
{
    BIT_r_0(H);
}

void CPU::BIT_L_0()
{
    BIT_r_0(L);
}

void CPU::BIT_pHL_0()
{
    F = ((mem->read8(HL) & 0x01) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 0 of given register.


void CPU::BIT_r_1(unsigned char r)
{
    F = ((r & 0x02) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region BIT_r_1 implementations
void CPU::BIT_A_1()
{
    BIT_r_1(A);
}

void CPU::BIT_B_1()
{
    BIT_r_1(B);
}

void CPU::BIT_C_1()
{
    BIT_r_1(C);
}

void CPU::BIT_D_1()
{
    BIT_r_1(D);
}

void CPU::BIT_E_1()
{
    BIT_r_1(E);
}

void CPU::BIT_H_1()
{
    BIT_r_1(H);
}

void CPU::BIT_L_1()
{
    BIT_r_1(L);
}

void CPU::BIT_pHL_1()
{
    F = ((mem->read8(HL) & 0x02) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 1 of given register.