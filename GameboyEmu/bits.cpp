#include "cpu.h"


/*=================================================
BIT TESTS
=================================================*/

//BIT 0
inline void CPU::BIT_r_0(unsigned char r)
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


//BIT 1
inline void CPU::BIT_r_1(unsigned char r)
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


//BIT 2
inline void CPU::BIT_r_2(unsigned char r)
{
    F = ((r & 0x04) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region BIT_r_2 implementations
void CPU::BIT_A_2()
{
    BIT_r_2(A);
}

void CPU::BIT_B_2()
{
    BIT_r_2(B);
}

void CPU::BIT_C_2()
{
    BIT_r_2(C);
}

void CPU::BIT_D_2()
{
    BIT_r_2(D);
}

void CPU::BIT_E_2()
{
    BIT_r_2(E);
}

void CPU::BIT_H_2()
{
    BIT_r_2(H);
}

void CPU::BIT_L_2()
{
    BIT_r_2(L);
}

void CPU::BIT_pHL_2()
{
    F = ((mem->read8(HL) & 0x04) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 2 of given register.


//BIT 3
inline void CPU::BIT_r_3(unsigned char r)
{
    F = ((r & 0x08) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region BIT_r_3 implementations
void CPU::BIT_A_3()
{
    BIT_r_3(A);
}

void CPU::BIT_B_3()
{
    BIT_r_3(B);
}

void CPU::BIT_C_3()
{
    BIT_r_3(C);
}

void CPU::BIT_D_3()
{
    BIT_r_3(D);
}

void CPU::BIT_E_3()
{
    BIT_r_3(E);
}

void CPU::BIT_H_3()
{
    BIT_r_3(H);
}

void CPU::BIT_L_3()
{
    BIT_r_3(L);
}

void CPU::BIT_pHL_3()
{
    F = ((mem->read8(HL) & 0x08) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 3 of given register.


//BIT 4
inline void CPU::BIT_r_4(unsigned char r)
{
    F = ((r & 0x10) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region BIT_r_4 implementations
void CPU::BIT_A_4()
{
    BIT_r_4(A);
}

void CPU::BIT_B_4()
{
    BIT_r_4(B);
}

void CPU::BIT_C_4()
{
    BIT_r_4(C);
}

void CPU::BIT_D_4()
{
    BIT_r_4(D);
}

void CPU::BIT_E_4()
{
    BIT_r_4(E);
}

void CPU::BIT_H_4()
{
    BIT_r_4(H);
}

void CPU::BIT_L_4()
{
    BIT_r_4(L);
}

void CPU::BIT_pHL_4()
{
    F = ((mem->read8(HL) & 0x10) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 4 of given register.


//BIT 5
inline void CPU::BIT_r_5(unsigned char r)
{
    F = ((r & 0x20) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region BIT_r_5 implementations
void CPU::BIT_A_5()
{
    BIT_r_5(A);
}

void CPU::BIT_B_5()
{
    BIT_r_5(B);
}

void CPU::BIT_C_5()
{
    BIT_r_5(C);
}

void CPU::BIT_D_5()
{
    BIT_r_5(D);
}

void CPU::BIT_E_5()
{
    BIT_r_5(E);
}

void CPU::BIT_H_5()
{
    BIT_r_5(H);
}

void CPU::BIT_L_5()
{
    BIT_r_5(L);
}

void CPU::BIT_pHL_5()
{
    F = ((mem->read8(HL) & 0x20) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 5 of given register.


//BIT 6
inline void CPU::BIT_r_6(unsigned char r)
{
    F = ((r & 0x40) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region BIT_r_6 implementations
void CPU::BIT_A_6()
{
    BIT_r_6(A);
}

void CPU::BIT_B_6()
{
    BIT_r_6(B);
}

void CPU::BIT_C_6()
{
    BIT_r_6(C);
}

void CPU::BIT_D_6()
{
    BIT_r_6(D);
}

void CPU::BIT_E_6()
{
    BIT_r_6(E);
}

void CPU::BIT_H_6()
{
    BIT_r_6(H);
}

void CPU::BIT_L_6()
{
    BIT_r_6(L);
}

void CPU::BIT_pHL_6()
{
    F = ((mem->read8(HL) & 0x40) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 6 of given register.


//BIT 7
inline void CPU::BIT_r_7(unsigned char r)
{
    F = ((r & 0x80) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region BIT_r_7 implementations
void CPU::BIT_A_7()
{
    BIT_r_7(A);
}

void CPU::BIT_B_7()
{
    BIT_r_7(B);
}

void CPU::BIT_C_7()
{
    BIT_r_7(C);
}

void CPU::BIT_D_7()
{
    BIT_r_7(D);
}

void CPU::BIT_E_7()
{
    BIT_r_7(E);
}

void CPU::BIT_H_7()
{
    BIT_r_7(H);
}

void CPU::BIT_L_7()
{
    BIT_r_7(L);
}

void CPU::BIT_pHL_7()
{
    F = ((mem->read8(HL) & 0x80) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 7 of given register.