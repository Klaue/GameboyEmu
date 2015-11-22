#include "cpu.h"


/*=================================================
                    BIT TESTS
=================================================*/

//BIT 0
inline void CPU::BIT_r_mask(unsigned char r, unsigned char mask)
{
    F = ((r & mask) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region Test bit 0 implementations
void CPU::BIT_A_0()
{
    BIT_r_mask(A, 0x01);
}

void CPU::BIT_B_0()
{
    BIT_r_mask(B, 0x01);
}

void CPU::BIT_C_0()
{
    BIT_r_mask(C, 0x01);
}

void CPU::BIT_D_0()
{
    BIT_r_mask(D, 0x01);
}

void CPU::BIT_E_0()
{
    BIT_r_mask(E, 0x01);
}

void CPU::BIT_H_0()
{
    BIT_r_mask(H, 0x01);
}

void CPU::BIT_L_0()
{
    BIT_r_mask(L, 0x01);
}

void CPU::BIT_pHL_0()
{
    F = ((mem->read8(HL) & 0x01) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 0 of given register.

#pragma region Test bit 1 implementations
void CPU::BIT_A_1()
{
    BIT_r_mask(A, 0x02);
}

void CPU::BIT_B_1()
{
    BIT_r_mask(B, 0x02);
}

void CPU::BIT_C_1()
{
    BIT_r_mask(C, 0x02);
}

void CPU::BIT_D_1()
{
    BIT_r_mask(D, 0x02);
}

void CPU::BIT_E_1()
{
    BIT_r_mask(E, 0x02);
}

void CPU::BIT_H_1()
{
    BIT_r_mask(H, 0x02);
}

void CPU::BIT_L_1()
{
    BIT_r_mask(L, 0x02);
}

void CPU::BIT_pHL_1()
{
    F = ((mem->read8(HL) & 0x02) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 1 of given register.

#pragma region Test bit 2 implementations
void CPU::BIT_A_2()
{
    BIT_r_mask(A, 0x04);
}

void CPU::BIT_B_2()
{
    BIT_r_mask(B, 0x04);
}

void CPU::BIT_C_2()
{
    BIT_r_mask(C, 0x04);
}

void CPU::BIT_D_2()
{
    BIT_r_mask(D, 0x04);
}

void CPU::BIT_E_2()
{
    BIT_r_mask(E, 0x04);
}

void CPU::BIT_H_2()
{
    BIT_r_mask(H, 0x04);
}

void CPU::BIT_L_2()
{
    BIT_r_mask(L, 0x04);
}

void CPU::BIT_pHL_2()
{
    F = ((mem->read8(HL) & 0x04) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 2 of given register.

#pragma region Test bit 3 implementations
void CPU::BIT_A_3()
{
    BIT_r_mask(A, 0x08);
}

void CPU::BIT_B_3()
{
    BIT_r_mask(B, 0x08);
}

void CPU::BIT_C_3()
{
    BIT_r_mask(C, 0x08);
}

void CPU::BIT_D_3()
{
    BIT_r_mask(D, 0x08);
}

void CPU::BIT_E_3()
{
    BIT_r_mask(E, 0x08);
}

void CPU::BIT_H_3()
{
    BIT_r_mask(H, 0x08);
}

void CPU::BIT_L_3()
{
    BIT_r_mask(L, 0x08);
}

void CPU::BIT_pHL_3()
{
    F = ((mem->read8(HL) & 0x08) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 3 of given register.

#pragma region Test bit 4 implementations
void CPU::BIT_A_4()
{
    BIT_r_mask(A, 0x10);
}

void CPU::BIT_B_4()
{
    BIT_r_mask(B, 0x10);
}

void CPU::BIT_C_4()
{
    BIT_r_mask(C, 0x10);
}

void CPU::BIT_D_4()
{
    BIT_r_mask(D, 0x10);
}

void CPU::BIT_E_4()
{
    BIT_r_mask(E, 0x10);
}

void CPU::BIT_H_4()
{
    BIT_r_mask(H, 0x10);
}

void CPU::BIT_L_4()
{
    BIT_r_mask(L, 0x10);
}

void CPU::BIT_pHL_4()
{
    F = ((mem->read8(HL) & 0x10) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 4 of given register.

#pragma region Test bit 5 implementations
void CPU::BIT_A_5()
{
    BIT_r_mask(A, 0x20);
}

void CPU::BIT_B_5()
{
    BIT_r_mask(B, 0x20);
}

void CPU::BIT_C_5()
{
    BIT_r_mask(C, 0x20);
}

void CPU::BIT_D_5()
{
    BIT_r_mask(D, 0x20);
}

void CPU::BIT_E_5()
{
    BIT_r_mask(E, 0x20);
}

void CPU::BIT_H_5()
{
    BIT_r_mask(H, 0x20);
}

void CPU::BIT_L_5()
{
    BIT_r_mask(L, 0x20);
}

void CPU::BIT_pHL_5()
{
    F = ((mem->read8(HL) & 0x20) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 5 of given register.

#pragma region Test bit 6 implementations
void CPU::BIT_A_6()
{
    BIT_r_mask(A, 0x40);
}

void CPU::BIT_B_6()
{
    BIT_r_mask(B, 0x40);
}

void CPU::BIT_C_6()
{
    BIT_r_mask(C, 0x40);
}

void CPU::BIT_D_6()
{
    BIT_r_mask(D, 0x40);
}

void CPU::BIT_E_6()
{
    BIT_r_mask(E, 0x40);
}

void CPU::BIT_H_6()
{
    BIT_r_mask(H, 0x40);
}

void CPU::BIT_L_6()
{
    BIT_r_mask(L, 0x40);
}

void CPU::BIT_pHL_6()
{
    F = ((mem->read8(HL) & 0x40) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 6 of given register.

#pragma region Test bit 7 implementations
void CPU::BIT_A_7()
{
    BIT_r_mask(A, 0x80);
}

void CPU::BIT_B_7()
{
    BIT_r_mask(B, 0x80);
}

void CPU::BIT_C_7()
{
    BIT_r_mask(C, 0x80);
}

void CPU::BIT_D_7()
{
    BIT_r_mask(D, 0x80);
}

void CPU::BIT_E_7()
{
    BIT_r_mask(E, 0x80);
}

void CPU::BIT_H_7()
{
    BIT_r_mask(H, 0x80);
}

void CPU::BIT_L_7()
{
    BIT_r_mask(L, 0x80);
}

void CPU::BIT_pHL_7()
{
    F = ((mem->read8(HL) & 0x80) ? 0 : ZERO_FLAG) | SUBTRACT_FLAG | ((F & CARRY_FLAG) ? CARRY_FLAG : 0);
    lastStepClk = 4;
}
#pragma endregion Tests bit 7 of given register.

/*==========================================
                BIT SETS
===========================================*/

//Changes the value of the masked bit in the given register to 1
inline void CPU::SET_r_mask(unsigned char & r, unsigned char mask)
{
    r |= mask;
    lastStepClk = 2;
}

#pragma region SET_r_0 implementations
void CPU::SET_A_0()
{
    SET_r_mask(A, 0x01);
}

void CPU::SET_B_0()
{
    SET_r_mask(B, 0x01);
}

void CPU::SET_C_0()
{
    SET_r_mask(C, 0x01);
}

void CPU::SET_D_0()
{
    SET_r_mask(D, 0x01);
}

void CPU::SET_E_0()
{
    SET_r_mask(E, 0x01);
}

void CPU::SET_H_0()
{
    SET_r_mask(H, 0x01);
}

void CPU::SET_L_0()
{
    SET_r_mask(L, 0x01);
}

void CPU::SET_pHL_0()
{
    mem->write8(HL, mem->read8(HL) | 0x01);
    lastStepClk = 4;
}
#pragma endregion Sets bit 0 of given register

#pragma region SET_r_1 implementations
void CPU::SET_A_1()
{
    SET_r_mask(A, 0x02);
}

void CPU::SET_B_1()
{
    SET_r_mask(B, 0x02);
}

void CPU::SET_C_1()
{
    SET_r_mask(C, 0x02);
}

void CPU::SET_D_1()
{
    SET_r_mask(D, 0x02);
}

void CPU::SET_E_1()
{
    SET_r_mask(E, 0x02);
}

void CPU::SET_H_1()
{
    SET_r_mask(H, 0x02);
}

void CPU::SET_L_1()
{
    SET_r_mask(L, 0x02);
}

void CPU::SET_pHL_1()
{
    mem->write8(HL, mem->read8(HL) | 0x02);
    lastStepClk = 4;
}
#pragma endregion Sets bit 1 of given register

#pragma region SET_r_2 implementations
void CPU::SET_A_2()
{
    SET_r_mask(A, 0x04);
}

void CPU::SET_B_2()
{
    SET_r_mask(B, 0x04);
}

void CPU::SET_C_2()
{
    SET_r_mask(C, 0x04);
}

void CPU::SET_D_2()
{
    SET_r_mask(D, 0x04);
}

void CPU::SET_E_2()
{
    SET_r_mask(E, 0x04);
}

void CPU::SET_H_2()
{
    SET_r_mask(H, 0x04);
}

void CPU::SET_L_2()
{
    SET_r_mask(L, 0x04);
}

void CPU::SET_pHL_2()
{
    mem->write8(HL, mem->read8(HL) | 0x04);
    lastStepClk = 4;
}
#pragma endregion Sets bit 2 of given register

#pragma region SET_r_3 implementations
void CPU::SET_A_3()
{
    SET_r_mask(A, 0x08);
}

void CPU::SET_B_3()
{
    SET_r_mask(B, 0x08);
}

void CPU::SET_C_3()
{
    SET_r_mask(C, 0x08);
}

void CPU::SET_D_3()
{
    SET_r_mask(D, 0x08);
}

void CPU::SET_E_3()
{
    SET_r_mask(E, 0x08);
}

void CPU::SET_H_3()
{
    SET_r_mask(H, 0x08);
}

void CPU::SET_L_3()
{
    SET_r_mask(L, 0x08);
}

void CPU::SET_pHL_3()
{
    mem->write8(HL, mem->read8(HL) | 0x08);
    lastStepClk = 4;
}
#pragma endregion Sets bit 3 of given register

#pragma region SET_r_4 implementations
void CPU::SET_A_4()
{
    SET_r_mask(A, 0x10);
}

void CPU::SET_B_4()
{
    SET_r_mask(B, 0x10);
}

void CPU::SET_C_4()
{
    SET_r_mask(C, 0x10);
}

void CPU::SET_D_4()
{
    SET_r_mask(D, 0x10);
}

void CPU::SET_E_4()
{
    SET_r_mask(E, 0x10);
}

void CPU::SET_H_4()
{
    SET_r_mask(H, 0x10);
}

void CPU::SET_L_4()
{
    SET_r_mask(L, 0x10);
}

void CPU::SET_pHL_4()
{
    mem->write8(HL, mem->read8(HL) | 0x10);
    lastStepClk = 4;
}
#pragma endregion Sets bit 4 of given register

#pragma region SET_r_5 implementations
void CPU::SET_A_5()
{
    SET_r_mask(A, 0x20);
}

void CPU::SET_B_5()
{
    SET_r_mask(B, 0x20);
}

void CPU::SET_C_5()
{
    SET_r_mask(C, 0x20);
}

void CPU::SET_D_5()
{
    SET_r_mask(D, 0x20);
}

void CPU::SET_E_5()
{
    SET_r_mask(E, 0x20);
}

void CPU::SET_H_5()
{
    SET_r_mask(H, 0x20);
}

void CPU::SET_L_5()
{
    SET_r_mask(L, 0x20);
}

void CPU::SET_pHL_5()
{
    mem->write8(HL, mem->read8(HL) | 0x20);
    lastStepClk = 4;
}
#pragma endregion Sets bit 5 of given register

#pragma region SET_r_6 implementations
void CPU::SET_A_6()
{
    SET_r_mask(A, 0x40);
}

void CPU::SET_B_6()
{
    SET_r_mask(B, 0x40);
}

void CPU::SET_C_6()
{
    SET_r_mask(C, 0x40);
}

void CPU::SET_D_6()
{
    SET_r_mask(D, 0x40);
}

void CPU::SET_E_6()
{
    SET_r_mask(E, 0x40);
}

void CPU::SET_H_6()
{
    SET_r_mask(H, 0x40);
}

void CPU::SET_L_6()
{
    SET_r_mask(L, 0x40);
}

void CPU::SET_pHL_6()
{
    mem->write8(HL, mem->read8(HL) | 0x40);
    lastStepClk = 4;
}
#pragma endregion Sets bit 6 of given register

#pragma region SET_r_7 implementations
void CPU::SET_A_7()
{
    SET_r_mask(A, 0x80);
}

void CPU::SET_B_7()
{
    SET_r_mask(B, 0x80);
}

void CPU::SET_C_7()
{
    SET_r_mask(C, 0x80);
}

void CPU::SET_D_7()
{
    SET_r_mask(D, 0x80);
}

void CPU::SET_E_7()
{
    SET_r_mask(E, 0x80);
}

void CPU::SET_H_7()
{
    SET_r_mask(H, 0x80);
}

void CPU::SET_L_7()
{
    SET_r_mask(L, 0x80);
}

void CPU::SET_pHL_7()
{
    mem->write8(HL, mem->read8(HL) | 0x80);
    lastStepClk = 4;
}
#pragma endregion Sets bit 7 of given register


/*==========================================
                BIT RESETS
===========================================*/

//Changes the value of the masked bit in the given register to 0
inline void CPU::RES_r_mask(unsigned char & r, unsigned char mask)
{
    r &= ~mask;
    lastStepClk = 2;
}

#pragma region RES_r_0 implementations
void CPU::RES_A_0()
{
    RES_r_mask(A, 0x01);
}

void CPU::RES_B_0()
{
    RES_r_mask(B, 0x01);
}

void CPU::RES_C_0()
{
    RES_r_mask(C, 0x01);
}

void CPU::RES_D_0()
{
    RES_r_mask(D, 0x01);
}

void CPU::RES_E_0()
{
    RES_r_mask(E, 0x01);
}

void CPU::RES_H_0()
{
    RES_r_mask(H, 0x01);
}

void CPU::RES_L_0()
{
    RES_r_mask(L, 0x01);
}

void CPU::RES_pHL_0()
{
    mem->write8(HL, 0xFE & mem->read8(HL));
    lastStepClk = 4;
}
#pragma endregion Resets bit 0 of given register

#pragma region RES_r_1 implementations
void CPU::RES_A_1()
{
    RES_r_mask(A, 0x02);
}

void CPU::RES_B_1()
{
    RES_r_mask(B, 0x02);
}

void CPU::RES_C_1()
{
    RES_r_mask(C, 0x02);
}

void CPU::RES_D_1()
{
    RES_r_mask(D, 0x02);
}

void CPU::RES_E_1()
{
    RES_r_mask(E, 0x02);
}

void CPU::RES_H_1()
{
    RES_r_mask(H, 0x02);
}

void CPU::RES_L_1()
{
    RES_r_mask(L, 0x02);
}

void CPU::RES_pHL_1()
{
    mem->write8(HL, 0xFD & mem->read8(HL));
    lastStepClk = 4;
}
#pragma endregion Resets bit 1 of given register

#pragma region RES_r_2 implementations
void CPU::RES_A_2()
{
    RES_r_mask(A, 0x04);
}

void CPU::RES_B_2()
{
    RES_r_mask(B, 0x04);
}

void CPU::RES_C_2()
{
    RES_r_mask(C, 0x04);
}

void CPU::RES_D_2()
{
    RES_r_mask(D, 0x04);
}

void CPU::RES_E_2()
{
    RES_r_mask(E, 0x04);
}

void CPU::RES_H_2()
{
    RES_r_mask(H, 0x04);
}

void CPU::RES_L_2()
{
    RES_r_mask(L, 0x04);
}

void CPU::RES_pHL_2()
{
    mem->write8(HL, 0xFB & mem->read8(HL));
    lastStepClk = 4;
}
#pragma endregion Resets bit 2 of given register

#pragma region RES_r_3 implementations
void CPU::RES_A_3()
{
    RES_r_mask(A, 0x08);
}

void CPU::RES_B_3()
{
    RES_r_mask(B, 0x08);
}

void CPU::RES_C_3()
{
    RES_r_mask(C, 0x08);
}

void CPU::RES_D_3()
{
    RES_r_mask(D, 0x08);
}

void CPU::RES_E_3()
{
    RES_r_mask(E, 0x08);
}

void CPU::RES_H_3()
{
    RES_r_mask(H, 0x08);
}

void CPU::RES_L_3()
{
    RES_r_mask(L, 0x08);
}

void CPU::RES_pHL_3()
{
    mem->write8(HL, 0xF7 & mem->read8(HL));
    lastStepClk = 4;
}
#pragma endregion Resets bit 3 of given register

#pragma region RES_r_4 implementations
void CPU::RES_A_4()
{
    RES_r_mask(A, 0x10);
}

void CPU::RES_B_4()
{
    RES_r_mask(B, 0x10);
}

void CPU::RES_C_4()
{
    RES_r_mask(C, 0x10);
}

void CPU::RES_D_4()
{
    RES_r_mask(D, 0x10);
}

void CPU::RES_E_4()
{
    RES_r_mask(E, 0x10);
}

void CPU::RES_H_4()
{
    RES_r_mask(H, 0x10);
}

void CPU::RES_L_4()
{
    RES_r_mask(L, 0x10);
}

void CPU::RES_pHL_4()
{
    mem->write8(HL, 0xEF & mem->read8(HL));
    lastStepClk = 4;
}
#pragma endregion Resets bit 4 of given register

#pragma region RES_r_5 implementations
void CPU::RES_A_5()
{
    RES_r_mask(A, 0x20);
}

void CPU::RES_B_5()
{
    RES_r_mask(B, 0x20);
}

void CPU::RES_C_5()
{
    RES_r_mask(C, 0x20);
}

void CPU::RES_D_5()
{
    RES_r_mask(D, 0x20);
}

void CPU::RES_E_5()
{
    RES_r_mask(E, 0x20);
}

void CPU::RES_H_5()
{
    RES_r_mask(H, 0x20);
}

void CPU::RES_L_5()
{
    RES_r_mask(L, 0x20);
}

void CPU::RES_pHL_5()
{
    mem->write8(HL, 0xDF & mem->read8(HL));
    lastStepClk = 4;
}
#pragma endregion Resets bit 5 of given register

#pragma region RES_r_6 implementations
void CPU::RES_A_6()
{
    RES_r_mask(A, 0x40);
}

void CPU::RES_B_6()
{
    RES_r_mask(B, 0x40);
}

void CPU::RES_C_6()
{
    RES_r_mask(C, 0x40);
}

void CPU::RES_D_6()
{
    RES_r_mask(D, 0x40);
}

void CPU::RES_E_6()
{
    RES_r_mask(E, 0x40);
}

void CPU::RES_H_6()
{
    RES_r_mask(H, 0x40);
}

void CPU::RES_L_6()
{
    RES_r_mask(L, 0x40);
}

void CPU::RES_pHL_6()
{
    mem->write8(HL, 0xBF & mem->read8(HL));
    lastStepClk = 4;
}
#pragma endregion Resets bit 6 of given register

#pragma region RES_r_7 implementations
void CPU::RES_A_7()
{
    RES_r_mask(A, 0x80);
}

void CPU::RES_B_7()
{
    RES_r_mask(B, 0x80);
}

void CPU::RES_C_7()
{
    RES_r_mask(C, 0x80);
}

void CPU::RES_D_7()
{
    RES_r_mask(D, 0x80);
}

void CPU::RES_E_7()
{
    RES_r_mask(E, 0x80);
}

void CPU::RES_H_7()
{
    RES_r_mask(H, 0x80);
}

void CPU::RES_L_7()
{
    RES_r_mask(L, 0x80);
}

void CPU::RES_pHL_7()
{
    mem->write8(HL, 0x7F & mem->read8(HL));
    lastStepClk = 4;
}
#pragma endregion Resets bit 7 of given register